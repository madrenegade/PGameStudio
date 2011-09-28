/* 
 * File:   SystemScene.cpp
 * Author: madrenegade
 * 
 * Created on September 23, 2011, 8:08 AM
 */

#include "Input/SystemScene.h"
#include "Input/InputTask.h"

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
        
        XmlReader::Node* controllerNode = sceneNode->first_node("controller");
        
        for(XmlReader::Node* node = controllerNode; node; node = node->next_sibling("controller"))
        {
            LOG(INFO) << "Configuring controller " << node->first_attribute("id")->value();
        }

        // create controllers
        // connect input events to controller events
//        const unsigned int escape = platformManager->getKeysym("Escape");
//        
//        buttons[escape] = Button();
    }

    tbb::task* SystemScene::getTask(tbb::task* parent)
    {
        return new(parent->allocate_child()) InputTask();
    }
    
    void SystemScene::onKeyPressed(const Core::Events::EventID& event, const boost::any& data)
    {
        
    }
    
    void SystemScene::onKeyReleased(const Core::Events::EventID& event, const boost::any& data)
    {
        
    }
}
