#include "Core/Events/EventHandler.h"

#include <glog/logging.h>
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <map>

namespace Core
{
	namespace Events
	{
        EventHandler::EventHandler()
        : serial()
        {
            
        }
        
        EventID EventHandler::registerEvent(const char* name)
        {
            RAW_CHECK(events.find(name) == events.end(), "Event is already registered");
            
            EventID id = serial.fetch_and_add(1);
            
            events[name] = id;
            
            signals[id].reset(new EventSignal);
            
            return id;
        }
        
        void EventHandler::registerEventHandler(const EventID& id, const EventHandlerFunction& fn)
        {
            // TODO check that id is valid
            
            signals[id]->connect(fn);
        }
        
        void EventHandler::pushEvent(const EventID& id, const boost::any& data)
        {
            eventQueue.push(std::make_pair(id, data));
        }
        
        void EventHandler::handleEvents()
        {
            EventData eventData;
            
            while(!eventQueue.empty())
            {
                if(eventQueue.try_pop(eventData))
                {
                    (*signals[eventData.first])(eventData.first, eventData.second);
                }
            }
        }
	}
}
