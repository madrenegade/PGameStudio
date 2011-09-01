/* 
 * File:   PoolManager.h
 * Author: madrenegade
 *
 * Created on September 1, 2011, 4:31 PM
 */

#ifndef UTILITIES_MEMORY_POOLMANAGER_H
#define	UTILITIES_MEMORY_POOLMANAGER_H

#include <boost/shared_ptr.hpp>
#include <map>

#include "Utilities/Memory/typedefs.h"

namespace Utilities
{
    namespace Memory
    {
        class Pool;
        
        class PoolManager
        {
        public:
            void add(Pool* pool, pool_id id);
            
            Pool* get(pool_id id) const;
            
        private:
            typedef std::map<pool_id, boost::shared_ptr<Pool> > PoolMap;
            PoolMap pools;
            
            void assertPoolExists(pool_id id) const;
            void assertPoolDoesNotExist(pool_id id) const;
            bool exists(pool_id id) const;
        };
    }
}


#endif	/* UTILITIES_MEMORY_POOLMANAGER_H */

