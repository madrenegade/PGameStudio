/* 
 * File:   typedef.h
 * Author: madrenegade
 *
 * Created on September 7, 2011, 5:13 PM
 */

#ifndef CORE_EVENTS_TYPEDEF_H
#define	CORE_EVENTS_TYPEDEF_H

#include <boost/function.hpp>
#include <boost/signal.hpp>

namespace Core
{
    namespace Events
    {
        typedef long EventID;
        
        typedef boost::function<void (const EventID& event, const boost::any& data)> EventHandlerFunction;
        typedef boost::signal<void (const EventID& event, const boost::any& data)> EventSignal;
    }
}

#endif	/* CORE_EVENTS_TYPEDEF_H */

