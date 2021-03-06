#include "Platform/Editor/Platform.h"

#include "Utilities/Memory/MemoryManager.h"

extern "C"
{

    std::shared_ptr<Platform::PlatformImpl> create(Utilities::Memory::MemoryManager* const memory)
    {
        return memory->construct(Platform::Editor::Platform());
    }
}
