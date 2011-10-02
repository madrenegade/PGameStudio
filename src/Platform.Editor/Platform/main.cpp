#include "Platform/Editor/Platform.h"

#include "Utilities/Memory/MemoryManager.h"

extern "C"
{

    boost::shared_ptr<Platform::PlatformImpl> create(const Utilities::Memory::MemoryManager::Ptr& memory)
    {
        return memory->construct(Platform::Editor::Platform());
    }
}
