/* 
 * File:   EffectManager.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 9:49 AM
 */

#ifndef RENDERER_EFFECTMANAGER_H
#define	RENDERER_EFFECTMANAGER_H

#include <map>
#include <boost/shared_ptr.hpp>

#include "Utilities/Memory/typedefs.h"

namespace Utilities
{
    namespace Memory
    {
        class MemoryManager;
    }
    
    namespace IO
    {
        class File;
    }
}

namespace Renderer
{
    class Effect;
    
    class EffectManager
    {
    public:
        EffectManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                            Utilities::Memory::pool_id pool);
        ~EffectManager();
        
        void createFrom(const std::pair<unsigned long, Utilities::IO::File>& request);
        
        bool isLoaded(unsigned long id) const;
        
        Effect* get(unsigned long id) const;
        
    private:
        boost::shared_ptr<Utilities::Memory::MemoryManager> memory;
        Utilities::Memory::pool_id pool;
        
        typedef std::map<unsigned long, boost::shared_ptr<Effect>> EffectMap;
        EffectMap effects;
    };
}

#endif	/* RENDERER_EFFECTMANAGER_H */

