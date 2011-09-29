#include "Core/Events/EventManager.h"
#include "Utilities/Memory/STLAllocator.h"

#include <glog/logging.h>
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <map>

using namespace Utilities::Memory;

namespace Core
{
	namespace Events
	{
        EventManager::EventManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager)
        : memory(memoryManager), serial()
        {
        }
        
        EventManager::~EventManager()
        {
        }
        
        EventID EventManager::registerEvent(const char* const name)
        {
            RAW_VLOG(2, "Registering event %s", name);
            
            RAW_CHECK(events.find(name) == events.end(), "Event is already registered");
            
            const EventID id = serial.fetch_and_add(1);
            
            events[name] = id;
            
            signals[id].reset(new EventSignal());
            
            return id;
        }
        
        EventID EventManager::getEventID(const char* const name) const
        {
            RAW_CHECK(events.find(name) != events.end(), (std::string("Event is not registered: ") + name).c_str());
            
            return events.at(name);
        }
        
        void EventManager::registerEventHandler(const EventID& id, const EventHandlerFunction& fn)
        {
            signals[id]->connect(fn);
        }
        
        void EventManager::pushEvent(const EventID& id, const boost::any& data)
        {
            eventQueue.push(std::make_pair(id, data));
        }
        
        void EventManager::handleEvents()
        {
            EventData eventData;
            
            while(!eventQueue.empty())
            {
                if(eventQueue.try_pop(eventData))
                {
#ifdef DEBUG
                    if(signals[eventData.first]->empty())
                    {
                        LOG(WARNING) << "Unhandled event " << getEventName(eventData.first);
                    }
#endif
                    (*signals[eventData.first])(eventData.first, eventData.second);
                }
            }
        }
        
#ifdef DEBUG
        String EventManager::getEventName(const EventID& id) const
        {
            for(auto i = events.begin(); i != events.end(); ++i)
            {
                if(i->second == id)
                {
                    return i->first;
                }
            }
            
            return "UNKNOWN";
        }
#endif
	}
}
