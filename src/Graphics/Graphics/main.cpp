#include "Graphics/SystemScene.h"
#include "Utilities/Memory/MemoryManager.h"

extern "C"
{
    boost::shared_ptr<Core::SystemScene> createSystemScene(Utilities::Memory::MemoryManager* const memory)
    {
        return memory->construct(Graphics::SystemScene());
    }
}
