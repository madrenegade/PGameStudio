/*
 * File:   StopWatch.cpp
 * Author: madrenegade
 *
 * Created on September 9, 2011, 9:25 AM
 */

#include "Utilities/StopWatch.h"

#include <glog/logging.h>
#include <glog/raw_logging.h>

typedef std::chrono::duration<long, std::ratio<1, 1000>> ms;

namespace Utilities
{
    StopWatch::StopWatch(const char* const name)
        : name(name), start(std::chrono::system_clock::now())
    {}

    StopWatch::~StopWatch()
    {
        auto end = std::chrono::system_clock::now();

        RAW_LOG_INFO("%s: %li ms", name.c_str(), std::chrono::duration_cast<ms> (end - start).count());
    }
}


