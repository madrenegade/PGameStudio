/* 
 * File:   SystemScene.cpp
 * Author: madrenegade
 * 
 * Created on September 23, 2011, 8:08 AM
 */

#include <X11/Xutil.h>

#include "Input/SystemScene.h"
#include "Input/InputTask.h"
#include "Input/Controller.h"
#include "Input/Button.h"
#include "Input/OneAxisControl.h"
#include "Input/TwoAxisControl.h"

#include "Utilities/Memory/MemoryPoolSettings.h"
#include "Utilities/functions.h"

#include "Core/Events/EventManager.h"
#include "Platform/PlatformManager.h"
#include "OneAxisControl.h"

using namespace Utilities::Memory;
using namespace Utilities::IO;

namespace Input
{
    const std::string SystemScene::EXTENSION("input");

    SystemScene::SystemScene()
    {
    }

    SystemScene::~SystemScene()
    {
    }

    void SystemScene::addOptionsTo(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties) const
    {
        const MemoryPoolSettings inputPool(1 * KByte, 1 * KByte, 128 * Byte,
            1 * KByte, 1 * KByte, 128 * Byte,
            1 * KByte, 1 * KByte, 128 * Byte);
        inputPool.addOptionsTo(properties, "Input");
    }

    const char* const SystemScene::getSceneFileExtension() const
    {
        return EXTENSION.c_str();
    }

    void SystemScene::initialize()
    {
        setScriptVar = eventManager->getEventID("SET_SCRIPT_VAR");
        // register input event handlers
        quit = eventManager->getEventID("QUIT");

        keyPressed = eventManager->getEventID("KEY_PRESSED");
        keyReleased = eventManager->getEventID("KEY_RELEASED");
        mouseButtonPressed = eventManager->getEventID("MOUSE_BUTTON_PRESSED");
        mouseButtonReleased = eventManager->getEventID("MOUSE_BUTTON_RELEASED");
        mouseMoved = eventManager->getEventID("MOUSE_MOVED");

        eventManager->registerEventHandler(keyPressed, boost::bind(&SystemScene::onButtonPressed, this, _1, _2));
        eventManager->registerEventHandler(keyReleased, boost::bind(&SystemScene::onButtonReleased, this, _1, _2));
        eventManager->registerEventHandler(mouseButtonPressed, boost::bind(&SystemScene::onButtonPressed, this, _1, _2));
        eventManager->registerEventHandler(mouseButtonReleased, boost::bind(&SystemScene::onButtonReleased, this, _1, _2));
        eventManager->registerEventHandler(mouseMoved, boost::bind(&SystemScene::onMouseMoved, this, _1, _2));
    }

    void SystemScene::load(const Utilities::IO::File& file)
    {
        const XmlReader reader(memoryManager, file);

        XmlReader::Node* sceneNode = reader.getDocument()->first_node("input");

        XmlReader::Node* firstControllerNode = sceneNode->first_node("controller");

        for (XmlReader::Node* controllerNode = firstControllerNode; controllerNode; controllerNode = controllerNode->next_sibling("controller"))
        {
            const String id(controllerNode->first_attribute("id")->value());

            VLOG(2) << "Configuring controller " << id;

            ControllerPtr controller = memoryManager->construct(Controller(id), pool);

            // TODO: check that controller does not exist
            controllers[id] = controller;

            XmlReader::Node* controlsNode = controllerNode->first_node("controls");

            processKeyboardControls(controller.get(), controlsNode->first_node("key"));
            processMouseButtonControls(controller.get(), controlsNode->first_node("button"));
            processMouseAxisControl(controller.get(), controlsNode->first_node("mouseAxis"));
        }
    }

    void SystemScene::processKeyboardControls(Controller* controller, XmlReader::Node* firstKeyNode)
    {
        for (XmlReader::Node* keyNode = firstKeyNode; keyNode; keyNode = keyNode->next_sibling("key"))
        {
            const String keyName(keyNode->first_attribute("name")->value());
            const unsigned int keysym = platformManager->getKeysym(keyName.c_str());

            processButtonControl(controller, keysym, keyNode);
        }
    }

    void SystemScene::processMouseButtonControls(Controller* controller, XmlReader::Node* firstButtonNode)
    {
        for (XmlReader::Node* buttonNode = firstButtonNode; buttonNode; buttonNode = buttonNode->next_sibling("button"))
        {
            const unsigned int button = Utilities::convertString<unsigned int>(buttonNode->first_attribute("id")->value());

            processButtonControl(controller, button, buttonNode);
        }
    }
    
    void SystemScene::processMouseAxisControl(Controller* controller, Utilities::IO::XmlReader::Node* mouseAxisNode)
    {
        if(!mouseAxisNode) return;
        
        const unsigned int axisControl = 0; // mouse is axis control 0
        processTwoAxisControl(controller, axisControl, mouseAxisNode);
    }

    void SystemScene::processButtonControl(Controller* controller, unsigned int button, Utilities::IO::XmlReader::Node* buttonNode)
    {
        XmlReader::Attribute* varAttribute = buttonNode->first_attribute("var");

        if (varAttribute)
        {
            controller->registerButton(button, varAttribute->value());
        }
        else
        {
            LOG(FATAL) << "Control '" << button << "' must have var attribute";
        }

        // TODO: check that key is not already bind to another controller
        keysymControllerMapping[button] = controller;
    }
    
    void SystemScene::processOneAxisControl(Controller* controller, unsigned int axisControl, Utilities::IO::XmlReader::Node* axisControlNode)
    {
        XmlReader::Attribute* varAttribute = axisControlNode->first_attribute("var");
        XmlReader::Attribute* deltaVarAttribute = axisControlNode->first_attribute("deltaVar");
        
        if(!varAttribute || !deltaVarAttribute)
        {
            LOG(FATAL) << "Axis control needs var and deltaVar attributes";
        }
        
        controller->registerOneAxisControl(axisControl, varAttribute->value(), deltaVarAttribute->value());
        idOneAxisControlMapping[axisControl] = controller;
    }
    
    void SystemScene::processTwoAxisControl(Controller* controller, unsigned int axisControl, Utilities::IO::XmlReader::Node* axisControlNode)
    {
        XmlReader::Attribute* xVarAttribute = axisControlNode->first_attribute("xVar");
        XmlReader::Attribute* yVarAttribute = axisControlNode->first_attribute("yVar");
        XmlReader::Attribute* xDeltaVarAttribute = axisControlNode->first_attribute("xDeltaVar");
        XmlReader::Attribute* yDeltaVarAttribute = axisControlNode->first_attribute("yDeltaVar");
        
        if(!xVarAttribute || !yVarAttribute || !xDeltaVarAttribute || !yDeltaVarAttribute)
        {
            LOG(FATAL) << "Axis control needs xVar, yVar, xDeltaVar and yDeltaVar attributes";
        }
        
        controller->registerTwoAxisControl(axisControl, xVarAttribute->value(), yVarAttribute->value(), 
                                           xDeltaVarAttribute->value(), yDeltaVarAttribute->value());
        idTwoAxisControlMapping[axisControl] = controller;
    }

    tbb::task* SystemScene::getTask(tbb::task* parent)
    {
        return new(parent->allocate_child()) InputTask(eventManager.get(), setScriptVar, dirtyButtons, dirtyOneAxisControls, dirtyTwoAxisControls);
    }

    void SystemScene::onButtonPressed(const Core::Events::EventID& event, const boost::any& data)
    {
        updateButton(boost::any_cast<unsigned int>(data), true);
    }

    void SystemScene::onButtonReleased(const Core::Events::EventID& event, const boost::any& data)
    {
        updateButton(boost::any_cast<unsigned int>(data), false);
    }
    
    void SystemScene::onMouseMoved(const Core::Events::EventID& event, const boost::any& data)
    {
        typedef std::pair<int, int> MouseMove;
        MouseMove xy = boost::any_cast<MouseMove>(data);
        
        updateTwoAxisControl(0, xy.first, xy.second);
    }

    void SystemScene::updateButton(unsigned int keysym, bool state)
    {
        if (keysymControllerMapping.find(keysym) == keysymControllerMapping.end())
        {
            return;
        }

        Controller* controller = keysymControllerMapping[keysym];

        Button* button = controller->getButtonFor(keysym);
        button->setState(state);

        dirtyButtons.push_back(button);
    }
    
    void SystemScene::updateOneAxisControl(unsigned int controlID, double x)
    {
        if (idOneAxisControlMapping.find(controlID) == idOneAxisControlMapping.end())
        {
            return;
        }
        
        Controller* controller = idOneAxisControlMapping[controlID];
        OneAxisControl* control = controller->getOneAxisControl(controlID);
        control->setState(x);
        
        dirtyOneAxisControls.push_back(control);
    }
    
    void SystemScene::updateTwoAxisControl(unsigned int controlID, double x, double y)
    {
        if (idTwoAxisControlMapping.find(controlID) == idTwoAxisControlMapping.end())
        {
            return;
        }
        
        Controller* controller = idTwoAxisControlMapping[controlID];
        
        TwoAxisControl* control = controller->getTwoAxisControl(controlID);
        control->setState(x, y);
        
        dirtyTwoAxisControls.push_back(control);
    }
}
