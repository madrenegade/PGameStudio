/*
 * File:   FileSystemFactory.h
 * Author: madrenegade
 *
 * Created on September 12, 2011, 2:01 PM
 */

#ifndef UTILITIES_IO_FILESYSTEMFACTORY_H
#define	UTILITIES_IO_FILESYSTEMFACTORY_H

#include "Utilities/Memory/MemoryManager.h"

#include <boost/shared_ptr.hpp>

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
            static boost::shared_ptr<FileSystem> create(const Memory::MemoryManager::Ptr& memory,
                    const boost::shared_ptr<Properties::PropertyManager>& properties);

        private:
            FileSystemFactory();
            ~FileSystemFactory();

            static boost::shared_ptr<Memory::Pool> createMemoryPool(const boost::shared_ptr<Properties::PropertyManager>& properties);
        };
    }
}


#endif	/* UTILITIES_IO_FILESYSTEMFACTORY_H */

