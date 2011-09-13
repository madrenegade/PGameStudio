/* 
 * File:   FileSystem.h
 * Author: madrenegade
 *
 * Created on September 12, 2011, 1:59 PM
 */

#ifndef UTILITIES_IO_FILESYSTEM_H
#define	UTILITIES_IO_FILESYSTEM_H

#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/IO/File.h"

namespace Utilities
{
    namespace IO
    {
        class FileHandle;
        
        class FileSystem
        {
        public:
            static void addOptionsTo(const Properties::PropertyManager::Ptr& properties);
            
            virtual ~FileSystem();
            
            File read(const char* path);
            
            void write(const char* filename, const File& file);
            
        protected:
            FileSystem(const Memory::MemoryManager::Ptr& memory, const Properties::PropertyManager::Ptr& properties);
            
            Memory::pool_id getMemoryPool() const;
            
            friend class FileSystemFactory;
            
            virtual void initialize(Memory::pool_id fsPool);
            
            virtual void mount(const char* path, const char* mountPoint) = 0;
            
            virtual bool exists(const char* path) const = 0;
            
            virtual size_t getFileSize(void* handle) const = 0;
            
            virtual void* openForReading(const char* path) = 0;
            virtual void* openForWriting(const char* filename) = 0;
            
            virtual void close(void* handle) = 0;
            
            virtual size_t read(void* handle, Memory::byte_pointer buffer, size_t size) = 0;
            virtual size_t write(void* handle, Memory::const_byte_pointer buffer, size_t size) = 0;
            
            virtual void setWriteDirectory(const char* organization, const char* appName) = 0;
            
        private:
            Memory::MemoryManager::Ptr memory;
            
            void mountDirectories();
            
            void assertPathExists(const char* path) const;
            
        protected:
            Properties::PropertyManager::Ptr properties;
            
            Memory::pool_id memoryPool;
        };
    }
}


#endif	/* UTILITIES_IO_FILESYSTEM_H */

