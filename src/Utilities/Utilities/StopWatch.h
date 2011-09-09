/* 
 * File:   StopWatch.h
 * Author: madrenegade
 *
 * Created on September 9, 2011, 9:25 AM
 */

#ifndef UTILITIES_STOPWATCH_H
#define	UTILITIES_STOPWATCH_H

#include <chrono>
#include <string>

namespace Utilities
{

    class StopWatch
    {
    public:
        /**
         * Start measuring time.
         */
        StopWatch(const char* name);
        
        /**
         * Stop measurment output the elapsed time in milliseconds
         */
        ~StopWatch();
        
    private:
        std::string name;
        
        std::chrono::time_point<std::chrono::system_clock> start;
    };
}

#endif	/* UTILITIES_STOPWATCH_H */

