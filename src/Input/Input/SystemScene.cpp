/* 
 * File:   SystemScene.cpp
 * Author: madrenegade
 * 
 * Created on September 23, 2011, 8:08 AM
 */

#include "Input/SystemScene.h"
#include "Input/InputTask.h"
#include "Input/Controller.h"

#include "Utilities/Memory/MemoryPoolSettings.h"
#include "Utilities/IO/XmlReader.h"

#include "Core/Events/EventManager.h"
#include "Platform/PlatformManager.h"

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
        // register input event handlers
        quit = eventManager->getEventID("QUIT");

        keyPressed = eventManager->getEventID("KEY_PRESSED");
        keyReleased = eventManager->getEventID("KEY_RELEASED");

        eventManager->registerEventHandler(keyPressed, boost::bind(&SystemScene::onKeyPressed, this, _1, _2));
        eventManager->registerEventHandler(keyReleased, boost::bind(&SystemScene::onKeyReleased, this, _1, _2));
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

            XmlReader::Node* firstKeyNode = controlsNode->first_node("key");
            for (XmlReader::Node* keyNode = firstKeyNode; keyNode; keyNode = keyNode->next_sibling("key"))
            {
                const String event(keyNode->first_attribute("event")->value());
                const Core::Events::EventID eventID = eventManager->getEventID(event.c_str());
                
                const String keyName(keyNode->first_attribute("name")->value());
                const unsigned int keysym = platformManager->getKeysym(keyName.c_str());

                controller->registerButton(keysym, eventID);

                // TODO: check that key is not already bind to another controller
                keysymControllerMapping[keysym] = controller.get();
            }

            // TODO: read other controls
        }
    }

    tbb::task* SystemScene::getTask(tbb::task* parent)
    {
        return new(parent->allocate_child()) InputTask(eventManager.get(), dirtyButtons);
    }

    void SystemScene::onKeyPressed(const Core::Events::EventID& event, const boost::any& data)
    {
        const unsigned int keysym = boost::any_cast<unsigned int>(data);
        
        updateButton(keysym, true);
    }

    void SystemScene::onKeyReleased(const Core::Events::EventID& event, const boost::any& data)
    {
        const unsigned int keysym = boost::any_cast<unsigned int>(data);
        
        updateButton(keysym, false);
    }
    
    void SystemScene::updateButton(unsigned int keysym, bool state)
    {
        if(keysymControllerMapping.find(keysym) == keysymControllerMapping.end())
        {
            return;
        }
        
        Controller* controller = keysymControllerMapping[keysym];
        
        Button* button = controller->getButtonFor(keysym);
        button->setState(state);
        
        dirtyButtons.push_back(button);
    }
}
