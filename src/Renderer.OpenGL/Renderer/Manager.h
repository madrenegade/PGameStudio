/* 
 * File:   Manager.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 1:17 PM
 */

#ifndef RENDERER_MANAGER_H
#define	RENDERER_MANAGER_H

#include <map>
#include <boost/shared_ptr.hpp>

#include "Utilities/Memory/typedefs.h"
#include "Utilities/Memory/MemoryManager.h"

namespace Renderer
{

    template<typename T, typename RequestType, typename ObjectInitializerType>
    class Manager
    {
    public:
        Manager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                Utilities::Memory::pool_id pool)
        : memory(memoryManager), pool(pool)
        {  
        }
        
        void createFrom(const RequestType& request)
        {
            boost::shared_ptr<T> object = memory->construct(T(), pool);
            ObjectInitializerType::initialize(object, request);
            
            data[request.id] = object;
        }
        
        bool isLoaded(unsigned long id) const
        {
            return data.find(id) != data.end();
        }
        
        T* get(unsigned long id) const
        {
            return data.at(id).get();
        }

    private:
        boost::shared_ptr<Utilities::Memory::MemoryManager> memory;
        Utilities::Memory::pool_id pool;

        typedef std::map<unsigned long, boost::shared_ptr<T> > DataMap;
        DataMap data;
    };
}

#endif	/* RENDERER_MANAGER_H */

