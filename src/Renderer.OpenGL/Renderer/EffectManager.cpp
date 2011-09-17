/* 
 * File:   EffectManager.cpp
 * Author: madrenegade
 * 
 * Created on September 17, 2011, 9:49 AM
 */

#include "Renderer/EffectManager.h"
#include "Renderer/Effect.h"

#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/IO/File.h"

namespace Renderer
{

    EffectManager::EffectManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                                 Utilities::Memory::pool_id pool)
    : memory(memoryManager), pool(pool)
    {
    }

    EffectManager::~EffectManager()
    {
    }
    
    void EffectManager::createFrom(const std::pair<unsigned long, Utilities::IO::File>& request)
    {
        boost::shared_ptr<Effect> effect = memory->construct(Effect(), pool);
        std::string code;
        code.assign(request.second.getData(), request.second.getSize());
        
        effect->load(code.c_str());
        
        effects[request.first] = effect;
    }
    
    bool EffectManager::isLoaded(unsigned long id) const
    {
        return effects.find(id) != effects.end();
    }
    
    Effect* EffectManager::get(unsigned long id) const
    {
        return effects.at(id).get();
    }
}
