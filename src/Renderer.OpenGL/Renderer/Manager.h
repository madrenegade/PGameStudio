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

#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>

#include "Utilities/Memory/typedefs.h"
#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/Memory/STLAllocator.h"

namespace Renderer
{

    template<typename T, typename RequestType, typename ObjectInitializerType>
    class Manager
    {
    public:

        Manager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                Utilities::Memory::pool_id pool)
        : currentID(), memory(memoryManager), pool(pool)
        {
        }

        void clear()
        {
            data.clear();
        }

        unsigned long queueRequest(RequestType& request)
        {
            unsigned long id = currentID.fetch_and_add(1);

            request.id = id;
            requests.push(request);

            return id;
        }

        void processRequests()
        {
            RequestType request;

            while (!requests.empty())
            {
                if (requests.try_pop(request))
                {
                    VLOG(2) << "Handling request with id " << request.id;

                    boost::shared_ptr<T> object = memory->construct(T(), pool);
                    ObjectInitializerType::initialize(object, request);

                    data[request.id] = object;
                }
            }
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
        tbb::atomic<unsigned long> currentID;

        boost::shared_ptr<Utilities::Memory::MemoryManager> memory;
        Utilities::Memory::pool_id pool;

        typedef boost::shared_ptr<T> pointer;

        typedef std::pair<const unsigned long, pointer> DataMapEntry;
        typedef Utilities::Memory::STLAllocator<DataMapEntry> DataMapEntryAllocator;
        typedef std::map<unsigned long, pointer, std::less<unsigned long>, DataMapEntryAllocator> DataMap;

        DataMap data;

        tbb::concurrent_queue<RequestType> requests;
    };
}

#endif	/* RENDERER_MANAGER_H */

