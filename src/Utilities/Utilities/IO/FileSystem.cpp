/*
 * File:   FileSystem.cpp
 * Author: madrenegade
 *
 * Created on September 12, 2011, 1:59 PM
 */
#include "Utilities/IO/FileSystem.h"
#include "Utilities/IO/XmlReader.h"
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

        void FileSystem::addOptionsTo(PropertyManager* const properties)
        {
            // FIXME: DCHECK_NE(properties, nullptr);

            MemoryPoolSettings fileSystemPool(1 * KByte, 1 * KByte, 128 * Byte,
                                              1 * KByte, 1 * KByte, 128 * Byte,
                                              1 * KByte, 1 * KByte, 128 * Byte);
            fileSystemPool.addOptionsTo(properties, "FileSystem");

            po::options_description options("Filesystem options");

            options.add_options()
            ("FileSystem.backend", po::value<unsigned char>()->default_value(0), "The backend to use")
            ("FileSystem.mount", po::value<std::vector<std::string>>()->default_value(std::vector<std::string>(0), "")->composing(), "Directories and their mount points")
            ("FileSystem.organization", po::value<std::string > (), "An organization named used to determine the writable directory")
            ("FileSystem.appName", po::value<std::string > (), "The application name used to determine the writable directory");

            properties->addOptions(options);
        }

        FileSystem::FileSystem(Memory::MemoryManager* const memory, const Properties::PropertyManager* const properties)
            : memory(DCHECK_NOTNULL(memory)),
            properties(DCHECK_NOTNULL(properties)), memoryPool(0)
        {

        }

        FileSystem::~FileSystem()
        {

        }

        Memory::pool_id FileSystem::getMemoryPool() const
        {
            return memoryPool;
        }

        void FileSystem::initialize(const Memory::pool_id fsPool)
        {
            memoryPool = fsPool;

            mountDirectories();

            RAW_LOG_INFO("Setting write directory");
            setWriteDirectory(properties->get<std::string > ("FileSystem.organization").c_str(),
                              properties->get<std::string > ("FileSystem.appName").c_str());
        }

        File::Handle FileSystem::read(const char* const path) const
        {
            //FIXME: DCHECK_NE(path, nullptr);

            std::shared_ptr<void> handle(DCHECK_NOTNULL(openForReading(path)), boost::bind(&FileSystem::close, this, _1));

            const size_t fileSize = getFileSize(handle.get());

            CHECK_GT(fileSize, 0) << "Attemp to read empty file: " << path;

            const boost::shared_array<Memory::byte> data = memory->allocate<Memory::byte>(fileSize, memoryPool);

            const size_t bytesRead = read(handle.get(), data.get(), fileSize);

            if (bytesRead < fileSize)
            {
                throw std::runtime_error("File could not be read fully");
            }

            return memory->construct(File(data, fileSize));
        }

        std::shared_ptr<XmlReader> FileSystem::readXml(const char* const path) const
        {
            return readXml(read(DCHECK_NOTNULL(path)));
        }

        std::shared_ptr<XmlReader> FileSystem::readXml(const File::Handle& file) const
        {
            std::shared_ptr<XmlReader> reader = memory->construct(XmlReader(memory, memoryPool, file));
            return reader;
        }

        void FileSystem::write(const char* const filename, const File& file)
        {
            // FIXME: DCHECK_NE(filename, nullptr);
            // FIXME: DCHECK_NE(file.getData(), nullptr);
            DCHECK_GT(file.getSize(), 0);

            const std::shared_ptr<void> handle(DCHECK_NOTNULL(openForWriting(filename)), boost::bind(&FileSystem::close, this, _1));

            const size_t bytesWritten = write(handle.get(), file.getData(), file.getSize());

            if (bytesWritten < file.getSize())
            {
                throw std::runtime_error("File could not be fully written");
            }
        }

        void FileSystem::mountDirectories()
        {
            const std::vector<std::string> mounts(properties->get<std::vector<std::string> >("FileSystem.mount"));

            std::vector<std::string, Utilities::Memory::STLAllocator<std::string>> parts;

            for (size_t i = 0; i < mounts.size(); ++i)
            {
                boost::iter_split(parts, mounts.at(i), boost::first_finder("->"));
                boost::trim(parts[0]);
                boost::trim(parts[1]);

                RAW_LOG_INFO("Mounting directory '%s' to '%s'", parts.at(0).c_str(), parts.at(1).c_str());

                mount(parts.at(0).c_str(), parts.at(1).c_str());
            }
        }

        void FileSystem::assertPathExists(const char* const path) const
        {
            // FIXME: DCHECK_NE(path, nullptr);

            if (!exists(path))
            {
                throw FileNotFoundException(path);
            }
        }
    }
}
