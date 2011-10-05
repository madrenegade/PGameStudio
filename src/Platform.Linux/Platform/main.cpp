#include "Platform/Linux/Platform.h"

#include "Utilities/Memory/MemoryManager.h"

extern "C"
{

    std::shared_ptr<Platform::PlatformImpl> create(const Utilities::Memory::MemoryManager::Ptr& memory)
    {
        return memory->construct(Platform::Linux::Platform());
    }
}
