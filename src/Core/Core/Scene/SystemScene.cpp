/* 
 * File:   SystemScene.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 2:28 PM
 */

#include "Core/Scene/SystemScene.h"
#include "Utilities/Memory/typedefs.h"
#include "Utilities/IO/FileSystem.h"

namespace Core
{

    SystemScene::SystemScene()
    {
    }

    SystemScene::~SystemScene()
    {
    }
    
    void SystemScene::setMemoryManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager)
    {
        this->memoryManager = memoryManager;
    }
    
    void SystemScene::setMemoryPool(Utilities::Memory::pool_id pool)
    {
        this->pool = pool;
    }
    
    void SystemScene::setPlatformManager(const boost::shared_ptr<Platform::PlatformManager>& platformManager)
    {
        this->platformManager = platformManager;
    }
    
    void SystemScene::setEventManager(const boost::shared_ptr<Events::EventManager>& eventManager)
    {
        this->eventManager = eventManager;
    }
    
    void SystemScene::setFileSystem(const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem)
    {
        this->fileSystem = fileSystem;
    }
    
    void SystemScene::setProperties(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties)
    {
        this->properties = properties;
    }
}
