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
    /**
    * A simple stopwatch class for measuring and printing time.
    * The measurement starts in the constructor and ends with the lifetime of the
    * object.
    */
    class StopWatch
    {
    public:
        /**
         * Start measuring time.
         */
        StopWatch(const char* const name);

        /**
         * Stop measurment and output the elapsed time in milliseconds to the console.
         */
        ~StopWatch();

    private:
        std::string name;

        std::chrono::time_point<std::chrono::system_clock> start;
    };
}

#endif	/* UTILITIES_STOPWATCH_H */

