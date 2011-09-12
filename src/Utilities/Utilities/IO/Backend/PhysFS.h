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
                PhysFS(const Memory::MemoryManager::Ptr& memory, const boost::shared_ptr<Properties::PropertyManager>& properties);
                virtual ~PhysFS();

                virtual void initialize();

            protected:
                virtual void mount(const char* path, const char* mountPoint);

                virtual bool exists(const char* path) const;

                virtual size_t getFileSize(void* handle) const;

                virtual void* openForReading(const char* path);
                virtual void* openForWriting(const char* filename);
                
                virtual void close(void* handle);
                
                virtual size_t read(void* handle, Memory::pointer buffer, size_t size);
                virtual size_t write(void* handle, Memory::const_pointer buffer, size_t size);
                
                virtual void setWriteDirectory(const char* organization, const char* appName);

                void checkVersion() const;
                void logError() const;
            };
        }
    }
}


#endif	/* UTILITIES_IO_PHYSFS_H */

