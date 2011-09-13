/* 
 * File:   Platform.cpp
 * Author: madrenegade
 * 
 * Created on September 13, 2011, 12:09 PM
 */

#include "Platform/Linux/Platform.h"

#include <glog/logging.h>

namespace Platform
{
    namespace Linux
    {

        Platform::Platform()
        {
            LOG(INFO) << "Platform created";
        }

        Platform::~Platform()
        {
            LOG(INFO) << "Platform destroyed";
        }
    }
}


