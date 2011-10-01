#ifndef CORE_EVENTS_EVENTHANDLER_H
#define CORE_EVENTS_EVENTHANDLER_H

#include "Core/Events/typedefs.h"
#include "Utilities/Memory/MemoryManager.h"
#include "Utilities/string.h"

#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>

namespace Core
{
    namespace Events
    {
        /**
         * This event handler class is designed for systems that use threads.
         * It is meant to be used like this: different threads can push events and
         * after all sub systems have done their work the event handlers will be called in serial.
         */
        class EventManager
        {
        public:
            EventManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager);
            ~EventManager();

            /**
             * Register an event and generate an ID for it.
             * NOT THREAD SAFE
             * @param name - the event name
             * @return the generated ID
             */
            EventID registerEvent(const char* const name);

            /**
             * Get the id of a registered event.
             * @param name - the name of the event
             */
            EventID getEventID(const char* const name) const;

            /**
             * Register an event handler so that it is autmatically called.
             * The event handling is done at the end of a frame in serial. So if your
             * event handler function takes some time to execute you should consider
             * pushing the event onto a local event queue and handle it during the next frame.
             * NOT THREAD SAFE
             * @param id - the event to register the handler for
             * @param fn - the event handler function to register
             */
            void registerEventHandler(const EventID& id, const EventHandlerFunction& fn);

            template<typename T>
            void pushEvent(const EventID& id, const T& data)
            {
                pushEvent(id, boost::any(data));
            }

            /**
             * Push an event into the event queue.
             * This method is thread safe to allow pushing from the various
             * sub systems which possibly run in different threads.
             * @param id - the event id
             * @param data - the data associated with this event
             */
            void pushEvent(const EventID& id, const boost::any& data);

            /**
             * Process all events. This calls all registered event handler functions
             * for the events that where pushed until the last invocation of this function.
             * NOT THREAD SAFE
             */
            void handleEvents();

        private:
#ifdef DEBUG
            String getEventName(const EventID& id) const;
#endif

            const boost::shared_ptr<Utilities::Memory::MemoryManager> memory;

            typedef std::pair<const String, EventID> EventMapEntry;
            typedef std::pair<const EventID, boost::shared_ptr<EventSignal>> SignalMapEntry;

            typedef Utilities::Memory::STLAllocator<EventMapEntry> EventMapAllocator;
            typedef Utilities::Memory::STLAllocator<SignalMapEntry> SignalMapAllocator;

            typedef std::map<String, EventID, std::less<String>, EventMapAllocator> EventMap;
            typedef std::map<EventID, boost::shared_ptr<EventSignal>, std::less<EventID>, SignalMapAllocator> SignalMap;

            EventMap events;
            SignalMap signals;

            tbb::atomic<EventID> serial;

            typedef std::pair<EventID, boost::any> EventData;
            tbb::concurrent_queue<EventData> eventQueue;
        };
    }
}

#endif // CORE_EVENTS_EVENTHANDLER_H
