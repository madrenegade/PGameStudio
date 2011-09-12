/* 
 * File:   FileSystemFactory.cpp
 * Author: madrenegade
 * 
 * Created on September 12, 2011, 2:01 PM
 */

#include <stdexcept>

#include "Utilities/IO/FileSystemFactory.h"
#include "Utilities/IO/Backend/PhysFS.h"

namespace Utilities
{
    namespace IO
    {

        boost::shared_ptr<FileSystem> FileSystemFactory::create(const Memory::MemoryManager::Ptr& memory, 
                                                                const boost::shared_ptr<Properties::PropertyManager>& properties,
                                                                FileSystemBackend backend)
        {
            boost::shared_ptr<FileSystem> fileSystem;
            
            switch (backend)
            {
                case FileSystemBackend::PhysFS:
                    fileSystem = memory->construct<Backend::PhysFS>(Backend::PhysFS(memory, properties));
                    break;

                default:
                    throw std::invalid_argument("unknown file system backend");
            }
            
            return fileSystem;
        }

        FileSystemFactory::FileSystemFactory()
        {
        }

        FileSystemFactory::~FileSystemFactory()
        {
        }
    }
}


