/*
 * File:   PhysFS.cpp
 * Author: madrenegade
 *
 * Created on September 12, 2011, 2:07 PM
 */

#include "Utilities/IO/Backend/PhysFS.h"
#include "Utilities/string.h"
#include <physfs.h>

namespace Utilities
{
    namespace IO
    {
        namespace Backend
        {

            PhysFS::PhysFS(Memory::MemoryManager* const memory, const Properties::PropertyManager* const properties)
                : FileSystem(memory, properties)
            {
            }

            PhysFS::~PhysFS()
            {
                if (PHYSFS_isInit())
                {
                    RAW_LOG_INFO("Deinitializing PhysFS");

                    if (PHYSFS_deinit() == 0)
                    {
                        logError();
                    }
                }
            }

            void PhysFS::initialize(const Memory::pool_id id)
            {
                PHYSFS_Version linked;
                PHYSFS_getLinkedVersion(&linked);

                RAW_LOG_INFO("Initializing PhysFS v%i.%i.%i", linked.major, linked.minor, linked.patch);

                checkVersion();

                if (PHYSFS_init(properties->get<std::string > ("argv0").c_str()) == 0)
                {
                    logError();
                }

                mount(".", 0);

                FileSystem::initialize(id);

                RAW_VLOG(1, "User dir: %s", PHYSFS_getUserDir());
                RAW_VLOG(1, "Write dir: %s", PHYSFS_getWriteDir());
            }

            void PhysFS::mount(const char* const path, const char* const mountPoint)
            {
                if (PHYSFS_mount(path, mountPoint, 1) == 0)
                {
                    logError();
                }
            }

            bool PhysFS::exists(const char* const path) const
            {
                return PHYSFS_exists(path) != 0 || PHYSFS_isDirectory(path) != 0;
            }

            size_t PhysFS::getFileSize(void* const handle) const
            {
                PHYSFS_File* internalHandle = static_cast<PHYSFS_File*> (handle);

                return PHYSFS_fileLength(internalHandle);
            }

            void* PhysFS::openForReading(const char* const path)
            {
#ifdef DEBUG
                RAW_LOG_INFO("Opening %s", path);

                void* handle = PHYSFS_openRead(path);

                if (handle == 0)
                {
                    logError();
                }

                return handle;
#else
                return PHYSFS_openRead(path);
#endif
            }

            void* PhysFS::openForWriting(const char* const filename)
            {
#ifdef DEBUG
                RAW_LOG_INFO("Opening %s for writing", filename);

                void* handle = PHYSFS_openWrite(filename);

                if(handle == 0)
                {
                    logError();
                }

                return handle;
#else
                return PHYSFS_openWrite(filename);
#endif
            }

            void PhysFS::close(void* const handle)
            {
                DCHECK(handle != 0);

                if(PHYSFS_close(static_cast<PHYSFS_File*>(handle)) == 0)
                {
                    logError();
                }
            }

            size_t PhysFS::read(void* const handle, Memory::byte_pointer const buffer, const size_t size)
            {
#ifdef DEBUG
                const size_t bytesRead = PHYSFS_read(static_cast<PHYSFS_File*>(handle), buffer, 1, size);

                if(bytesRead < size)
                {
                    logError();
                }

                return bytesRead;
#else
                return PHYSFS_read(static_cast<PHYSFS_File*>(handle), buffer, 1, size);
#endif
            }

            size_t PhysFS::write(void* const handle, Memory::const_byte_pointer const buffer, const size_t size)
            {
#ifdef DEBUG
                const size_t bytesWritten = PHYSFS_write(static_cast<PHYSFS_File*>(handle), buffer, 1, size);

                if(bytesWritten < size)
                {
                    logError();
                }

                return bytesWritten;
#else
                return PHYSFS_write(static_cast<PHYSFS_File*>(handle), buffer, 1, size);
#endif
            }

            void PhysFS::setWriteDirectory(const char* const organization, const char* const appName)
            {
                if(PHYSFS_setSaneConfig(organization, appName, 0, 0, 0) == 0)
                {
                    logError();
                }

                RAW_LOG_INFO("Write directory set to %s", PHYSFS_getWriteDir());
            }

            void PhysFS::checkVersion() const
            {
                PHYSFS_Version compiled;
                PHYSFS_VERSION(&compiled);

                PHYSFS_Version linked;
                PHYSFS_getLinkedVersion(&linked);

                if (compiled.major != linked.major ||
                        compiled.minor != linked.minor ||
                        compiled.patch != linked.patch)
                {
                    RAW_LOG_WARNING("Using PhysFS v%i.%i.%i but compiled against v%i.%i.%i",
                                    linked.major, linked.minor, linked.patch,
                                    compiled.major, compiled.minor, compiled.patch);
                }
            }

            void PhysFS::logError() const
            {
                RAW_LOG_ERROR("PhysFS error: %s", PHYSFS_getLastError());
            }
        }
    }
}


