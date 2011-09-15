/* 
 * File:   ExtractorProxy.cpp
 * Author: madrenegade
 * 
 * Created on September 15, 2011, 2:34 PM
 */

#include "Scripting/ExtractorProxy.h"

namespace Scripting
{

    ExtractorProxy::ExtractorProxy(Extractor* extractor)
    : extractor(extractor)
    {
    }

    ExtractorProxy::~ExtractorProxy()
    {
    }
}
