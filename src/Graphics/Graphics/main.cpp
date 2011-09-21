#include "Graphics/SystemScene.h"
#include "Utilities/Memory/MemoryManager.h"

extern "C"
{
    boost::shared_ptr<Core::SystemScene> createSystemScene(const Utilities::Memory::MemoryManager::Ptr& memory)
    {
        return memory->construct(Graphics::SystemScene());
    }
}
