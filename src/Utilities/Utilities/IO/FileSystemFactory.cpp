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

        boost::shared_ptr<FileSystem> FileSystemFactory::create(Memory::MemoryManager* const memory,
                const Properties::PropertyManager* const properties)
        {
            DCHECK_NOTNULL(memory);
            DCHECK_NOTNULL(properties);

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

        boost::shared_ptr<Memory::Pool> FileSystemFactory::createMemoryPool(const Properties::PropertyManager* const properties)
        {
            MemoryPoolSettings fsPoolSettings(MemoryPoolSettings::loadFrom(properties, "FileSystem"));

            boost::shared_ptr<Pool> pool = Pool::create("FileSystemPool", fsPoolSettings);

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


