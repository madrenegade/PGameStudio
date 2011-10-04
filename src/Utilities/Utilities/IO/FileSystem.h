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
        class XmlReader;

        class FileSystem
        {
        public:
            static void addOptionsTo(Properties::PropertyManager* const properties);

            virtual ~FileSystem();

            /**
             * Read a file into memory.
             * @param path - The name of the file to read.
             * @return A handle to the \ref Utilities::IO::File object containing
             * the data of the file.
             */
            File::Handle read(const char* const path);

            /**
             * Read a xml file into memory.
             * @param path - The name of the file to read.
             * @return An object of type \ref Utilities::IO::XmlReader to
             * navigate through the xml document.
             */
            boost::shared_ptr<XmlReader> readXml(const char* const path);

            /**
             * Read a xml file into memory.
             * @param file - The file containing the xml data.
             * @return An object of type \ref Utilities::IO::XmlReader to
             * navigate through the xml document.
             */
            boost::shared_ptr<XmlReader> readXml(const File::Handle& file);

            /**
             * Save a file in the writable directory. The writable directory is automatically determined using the settings.
             * @param filename - The name of the file to write to.
             * @param file - A \ref Utilities::IO::File object containing the data to write.
             */
            void write(const char* const filename, const File& file);

        protected:
            FileSystem(Memory::MemoryManager* const memory, const Properties::PropertyManager* const properties);

            Memory::pool_id getMemoryPool() const;

            friend class FileSystemFactory;

            virtual void initialize(const Memory::pool_id fsPool);

            virtual void mount(const char* const path, const char* const mountPoint) = 0;

            virtual bool exists(const char* const path) const = 0;

            virtual size_t getFileSize(void* const handle) const = 0;

            virtual void* openForReading(const char* const path) = 0;
            virtual void* openForWriting(const char* const filename) = 0;

            virtual void close(void* const handle) = 0;

            virtual size_t read(void* const handle, Memory::byte_pointer const buffer, const size_t size) = 0;
            virtual size_t write(void* const handle, Memory::const_byte_pointer const buffer, const size_t size) = 0;

            virtual void setWriteDirectory(const char* const organization, const char* const appName) = 0;

        private:
            Memory::MemoryManager* const memory;

            void mountDirectories();

            void assertPathExists(const char* const path) const;

        protected:
            const Properties::PropertyManager* const properties;
            Memory::pool_id memoryPool;
        };
    }
}


#endif	/* UTILITIES_IO_FILESYSTEM_H */

