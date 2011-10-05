/*
 * File:   FileSystemFactory.h
 * Author: madrenegade
 *
 * Created on September 12, 2011, 2:01 PM
 */

#ifndef UTILITIES_IO_FILESYSTEMFACTORY_H
#define	UTILITIES_IO_FILESYSTEMFACTORY_H

#include "Utilities/Memory/MemoryManager.h"



namespace Utilities
{
    namespace Properties
    {
        class PropertyManager;
    }

    namespace IO
    {
        class FileSystem;

        class FileSystemFactory
        {
        public:
            static std::shared_ptr<FileSystem> create(Memory::MemoryManager*const memory,
                    const Properties::PropertyManager* const properties);

        private:
            FileSystemFactory();
            ~FileSystemFactory();

            static std::shared_ptr<Memory::Pool> createMemoryPool(const Properties::PropertyManager* const properties);
        };
    }
}


#endif	/* UTILITIES_IO_FILESYSTEMFACTORY_H */

