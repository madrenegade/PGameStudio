/*
 * File:   PhysFS.h
 * Author: madrenegade
 *
 * Created on September 12, 2011, 2:07 PM
 */

#ifndef UTILITIES_IO_PHYSFS_H
#define	UTILITIES_IO_PHYSFS_H

#include "Utilities/IO/FileSystem.h"

namespace Utilities
{
    namespace IO
    {
        namespace Backend
        {

            class PhysFS : public FileSystem
            {
            public:
                PhysFS(Memory::MemoryManager* const memory, const Properties::PropertyManager* const properties);
                virtual ~PhysFS();

            protected:
                virtual void initialize(const Memory::pool_id id);

                virtual void mount(const char* const path, const char* const mountPoint);

                virtual bool exists(const char* const path) const;

                virtual size_t getFileSize(void* const handle) const;

                virtual void* openForReading(const char* const path);
                virtual void* openForWriting(const char* const filename);

                virtual void close(void* const handle);

                virtual size_t read(void* const handle, Memory::byte_pointer const buffer, const size_t size);
                virtual size_t write(void* const handle, Memory::const_byte_pointer const buffer, const size_t size);

                virtual void setWriteDirectory(const char* const organization, const char* const appName);

                void checkVersion() const;
                void logError() const;
            };
        }
    }
}


#endif	/* UTILITIES_IO_PHYSFS_H */

