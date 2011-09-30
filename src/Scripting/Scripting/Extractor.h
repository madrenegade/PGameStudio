/*
 * File:   Extractor.h
 * Author: madrenegade
 *
 * Created on September 15, 2011, 12:36 PM
 */

#ifndef SCRIPTING_EXTRACTOR_H
#define	SCRIPTING_EXTRACTOR_H

#include "Scripting/typedefs.h"
#include "Utilities/string.h"

extern "C"
{
#include <lua.h>
}

namespace Scripting
{
        class Extractor
        {
        public:
            Extractor(AnyVector& params, lua_State* const state);
            ~Extractor();

            void operator()(const bool& b);
            void operator()(const long& i);
            void operator()(const double& d);

            void operator()(const char* s);
            void operator()(const String& s);

        private:
            AnyVector& params;

            lua_State* const state;
            int stackIndex;
        };
}


#endif	/* SCRIPTING_EXTRACTOR_H */

