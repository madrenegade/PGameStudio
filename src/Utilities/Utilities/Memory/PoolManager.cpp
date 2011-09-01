/* 
 * File:   PoolManager.cpp
 * Author: madrenegade
 * 
 * Created on September 1, 2011, 4:31 PM
 */

#include <stdexcept>
#include <glog/logging.h>

#include "Utilities/Memory/PoolManager.h"
#include "Utilities/Memory/Pool.h"

namespace Utilities
{
    namespace Memory
    {
        void PoolManager::add(Pool* pool, pool_id id)
        {
            boost::shared_ptr<Pool> ptr(pool);
            
            assertPoolDoesNotExist(id);
            
            pools[id] = ptr;
        }
        
        Pool* PoolManager::get(pool_id id) const
        {
#ifdef DEBUG
            assertPoolExists(id);
#endif
            
            return pools.at(id).get();
        }
        
        void PoolManager::assertPoolExists(pool_id id) const
        {
           if(!exists(id))
           {
               LOG(ERROR) << "A memory pool with id " << id << " does not exist";
               
               throw new std::logic_error("Pool does not exist");
           }
        }
        
        void PoolManager::assertPoolDoesNotExist(pool_id id) const
        {
           if(exists(id))
           {
               LOG(ERROR) << "A memory pool with id " << id << " already exists";
               
               throw new std::logic_error("Pool already exists");
           }
        }
        
        bool PoolManager::exists(pool_id id) const
        {
            return pools.find(id) != pools.end();
        }
    }
}
