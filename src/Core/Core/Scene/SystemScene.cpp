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

    void SystemScene::setMemoryManager(Utilities::Memory::MemoryManager* const memoryManager)
    {
        this->memoryManager = memoryManager;
    }

    void SystemScene::setMemoryPool(const Utilities::Memory::pool_id& pool)
    {
        this->pool = pool;
    }

    void SystemScene::setPlatformManager(const Platform::PlatformManager* const platformManager)
    {
        this->platformManager = platformManager;
    }

    void SystemScene::setEventManager(Events::EventManager* const eventManager)
    {
        this->eventManager = eventManager;
    }

    void SystemScene::setFileSystem(Utilities::IO::FileSystem* const fileSystem)
    {
        this->fileSystem = fileSystem;
    }

    void SystemScene::setProperties(const Utilities::Properties::PropertyManager* const properties)
    {
        this->properties = properties;
    }
}
