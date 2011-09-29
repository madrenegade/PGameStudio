/*
 * File:   Extractor.h
 * Author: madrenegade
 *
 * Created on September 15, 2011, 12:24 PM
 */

#ifndef SCRIPTING_EXTRACTOR_H
#define	SCRIPTING_EXTRACTOR_H

#include "Scripting/typedefs.h"
#include "Utilities/string.h"

namespace Scripting
{
    class Extractor
    {
    public:
        virtual ~Extractor();

        virtual void extract(const bool& b) = 0;
        virtual void extract(const long& i) = 0;
        virtual void extract(const double& d) = 0;

        virtual void extract(const char* s) = 0;
        virtual void extract(const String& s) = 0;

    protected:
        Extractor(AnyVector& params);

        AnyVector& params;
    };
}

#endif	/* SCRIPTING_EXTRACTOR_H */

