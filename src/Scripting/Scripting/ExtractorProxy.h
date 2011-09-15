/* 
 * File:   ExtractorProxy.h
 * Author: madrenegade
 *
 * Created on September 15, 2011, 2:34 PM
 */

#ifndef SCRIPTING_EXTRACTORPROXY_H
#define	SCRIPTING_EXTRACTORPROXY_H

#include "Scripting/Extractor.h"

namespace Scripting
{

    class ExtractorProxy
    {
    public:
        ExtractorProxy(Extractor* extractor);
        ~ExtractorProxy();
        
        template< typename T >
        void operator()(T t)
        {
            extractor->extract(t);
        }
        
    private:
        Extractor* extractor;
    };
}

#endif	/* SCRIPTING_EXTRACTORPROXY_H */

