/* 
 * File:   Extractor.h
 * Author: madrenegade
 *
 * Created on September 15, 2011, 12:24 PM
 */

#ifndef SCRIPTING_EXTRACTOR_H
#define	SCRIPTING_EXTRACTOR_H

#include <glog/logging.h>
#include <typeinfo>
#include "Scripting/typedefs.h"

namespace Scripting
{

    /**
     * Really ugly class. extract cannot be pure virtual because the base class must be instantiated
     * to make boost::mpl work. So in extract the methods are invoked in the real implementation. If no such implementation
     * exists the app crashes without a good error message.
     * @param real
     * @param params
     */
    class Extractor
    {
    public:
        virtual ~Extractor();
        
        virtual void extract(const bool& b) = 0;
        virtual void extract(const long& i) = 0;
        virtual void extract(const double& d) = 0;
        
        virtual void extract(const char* s) = 0;
        virtual void extract(const std::string& s) = 0;
        
    protected:
        Extractor(AnyVector& params);
        
        AnyVector& params;
    };
}

#endif	/* SCRIPTING_EXTRACTOR_H */

