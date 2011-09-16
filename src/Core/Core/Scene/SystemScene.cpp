/* 
 * File:   SystemScene.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 2:28 PM
 */

#include "Core/Scene/SystemScene.h"
#include "Utilities/Memory/typedefs.h"

namespace Core
{

    SystemScene::SystemScene()
    {
    }

    SystemScene::~SystemScene()
    {
    }
    
    void SystemScene::initialize()
    {
        
    }
    
    void SystemScene::setMemoryManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager)
    {
        this->memoryManager = memoryManager;
    }
    
    void SystemScene::setPlatformManager(const boost::shared_ptr<Platform::PlatformManager>& platformManager)
    {
        this->platformManager = platformManager;
    }
    
    void SystemScene::setEventManager(const boost::shared_ptr<Events::EventManager>& eventManager)
    {
        this->eventManager = eventManager;
    }
}
