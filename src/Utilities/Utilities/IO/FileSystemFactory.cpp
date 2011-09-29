/* 
 * File:   FileSystemFactory.cpp
 * Author: madrenegade
 * 
 * Created on September 12, 2011, 2:01 PM
 */

#include <stdexcept>

#include "Utilities/IO/FileSystemFactory.h"
#include "Utilities/IO/FileSystemBackend.h"
#include "Utilities/IO/Backend/PhysFS.h"

using namespace Utilities::Memory;
using namespace Utilities::Properties;

namespace Utilities
{
    namespace IO
    {

        boost::shared_ptr<FileSystem> FileSystemFactory::create(const MemoryManager::Ptr& memory,
                                                                const boost::shared_ptr<PropertyManager>& properties)
        {
            const FileSystemBackend backend = valueOf<FileSystemBackend>(properties->get<unsigned char>("FileSystem.backend"));
            
            const pool_id pool = memory->registerMemoryPool(createMemoryPool(properties));
            
            boost::shared_ptr<FileSystem> fileSystem;

            switch (backend)
            {
                case FileSystemBackend::PhysFS:
                    fileSystem = memory->construct<Backend::PhysFS > (Backend::PhysFS(memory, properties), pool);
                    break;

                default:
                    throw std::invalid_argument("unknown file system backend");
            }

            fileSystem->initialize(pool);

            return fileSystem;
        }

        boost::shared_ptr<Memory::Pool> FileSystemFactory::createMemoryPool(const boost::shared_ptr<Properties::PropertyManager>& properties)
        {
            size_t soMax = properties->get<size_t > ("FileSystem.memory.smallObjects.maxSize");
            size_t soPage = properties->get<size_t > ("FileSystem.memory.smallObjects.pageSize");
            size_t soBlock = properties->get<size_t > ("FileSystem.memory.smallObjects.blockSize");

            size_t moMax = properties->get<size_t > ("FileSystem.memory.mediumObjects.maxSize");
            size_t moPage = properties->get<size_t > ("FileSystem.memory.mediumObjects.pageSize");
            size_t moBlock = properties->get<size_t > ("FileSystem.memory.mediumObjects.blockSize");

            size_t loMax = properties->get<size_t > ("FileSystem.memory.largeObjects.maxSize");
            size_t loPage = properties->get<size_t > ("FileSystem.memory.largeObjects.pageSize");
            size_t loBlock = properties->get<size_t > ("FileSystem.memory.largeObjects.blockSize");

            MemoryPoolSettings fsPoolSettings(
                soMax, soPage, soBlock,
                moMax, moPage, moBlock,
                loMax, loPage, loBlock);
            
            boost::shared_ptr<Pool> pool = Pool::create(fsPoolSettings);

            return pool;
        }

        FileSystemFactory::FileSystemFactory()
        {
        }

        FileSystemFactory::~FileSystemFactory()
        {
        }
    }
}


