/* 
 * File:   FileSystem.cpp
 * Author: madrenegade
 * 
 * Created on September 12, 2011, 1:59 PM
 */
#include "Utilities/IO/FileSystem.h"
#include "Utilities/IO/Exceptions/FileNotFoundException.h"
#include "Utilities/string.h"

#include <boost/algorithm/string.hpp>
#include <physfs.h>

using namespace Utilities::Properties;
using namespace Utilities::Memory;

namespace po = boost::program_options;

namespace Utilities
{
    namespace IO
    {

        void FileSystem::addOptionsTo(const PropertyManager::Ptr& properties)
        {
            po::options_description options("Filesystem options");

            options.add_options()
                ("FileSystem.backend", po::value<unsigned char>()->default_value(0), "The backend to use")
                ("FileSystem.mount", po::value<std::vector<std::string> >(), "Directories and their mount points")
                ("FileSystem.organization", po::value<std::string > (), "An organization named used to determine the writable directory")
                ("FileSystem.appName", po::value<std::string > (), "The application name used to determine the writable directory")

                ("FileSystem.memory.smallObjects.maxSize", po::value<size_t > ()->default_value(1 * KByte), "Maximum size for the small object area in the filesystem memory pool")
                ("FileSystem.memory.smallObjects.pageSize", po::value<size_t > ()->default_value(1 * KByte), "Page size for the small object area in the filesystem memory pool")
                ("FileSystem.memory.smallObjects.blockSize", po::value<size_t > ()->default_value(128 * Byte), "Block size for the small object area in the filesystem memory pool")

                ("FileSystem.memory.mediumObjects.maxSize", po::value<size_t > ()->default_value(1 * KByte), "Maximum size for the medium object area in the filesystem memory pool")
                ("FileSystem.memory.mediumObjects.pageSize", po::value<size_t > ()->default_value(1 * KByte), "Page size for the medium object area in the filesystem memory pool")
                ("FileSystem.memory.mediumObjects.blockSize", po::value<size_t > ()->default_value(128 * Byte), "Block size for the medium object area in the filesystem memory pool")

                ("FileSystem.memory.largeObjects.maxSize", po::value<size_t > ()->default_value(1 * KByte), "Maximum size for the large object area in the filesystem memory pool")
                ("FileSystem.memory.largeObjects.pageSize", po::value<size_t > ()->default_value(1 * KByte), "Page size for the large object area in the filesystem memory pool")
                ("FileSystem.memory.largeObjects.blockSize", po::value<size_t > ()->default_value(128 * Byte), "Block size for the large object area in the filesystem memory pool");

            properties->addOptions(options);
        }

        FileSystem::FileSystem(const Memory::MemoryManager::Ptr& memory, const PropertyManager::Ptr& properties)
        : memory(memory), properties(properties), memoryPool(0)
        {

        }

        FileSystem::~FileSystem()
        {

        }
        
        Memory::pool_id FileSystem::getMemoryPool() const
        {
            return memoryPool;
        }

        void FileSystem::initialize(Memory::pool_id fsPool)
        {
            memoryPool = fsPool;
            
            mountDirectories();

            RAW_LOG_INFO("Setting write directory");
            setWriteDirectory(properties->get<std::string > ("FileSystem.organization").c_str(),
                properties->get<std::string > ("FileSystem.appName").c_str());
        }

        File FileSystem::read(const char* path)
        {
            boost::shared_ptr<void> handle(openForReading(path), boost::bind(&FileSystem::close, this, _1));

            DCHECK(handle != 0);

            const size_t fileSize = getFileSize(handle.get());

            assert(fileSize > 0);

            boost::shared_array<Memory::byte> data = memory->allocate<Memory::byte > (fileSize, memoryPool);

            size_t bytesRead = read(handle.get(), data.get(), fileSize);

            if (bytesRead < fileSize)
            {
                throw std::runtime_error("File could not be read fully");
            }

            return File(data, fileSize);
        }

        void FileSystem::write(const char* filename, const File& file)
        {
            DCHECK(file.getSize() > 0);
            DCHECK(file.getData() != 0);

            boost::shared_ptr<void> handle(openForWriting(filename), boost::bind(&FileSystem::close, this, _1));

            DCHECK(handle != 0);

            size_t bytesWritten = write(handle.get(), file.getData(), file.getSize());

            if (bytesWritten < file.getSize())
            {
                throw std::runtime_error("File could not be fully written");
            }
        }

        void FileSystem::mountDirectories()
        {
            std::vector<std::string> mounts(properties->get<std::vector<std::string> >("FileSystem.mount"));

            std::vector<std::string> parts;

            for (size_t i = 0; i < mounts.size(); ++i)
            {
                boost::iter_split(parts, mounts.at(i), boost::first_finder("->"));
                boost::trim(parts[0]);
                boost::trim(parts[1]);

                RAW_LOG_INFO("Mounting directory '%s' to '%s'", parts.at(0).c_str(), parts.at(1).c_str());

                mount(parts.at(0).c_str(), parts.at(1).c_str());
            }
        }

        void FileSystem::assertPathExists(const char* path) const
        {
            if (!exists(path))
            {
                throw FileNotFoundException(path);
            }
        }
    }
}
