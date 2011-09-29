/*
 * File:   Extractor.h
 * Author: madrenegade
 *
 * Created on September 15, 2011, 12:36 PM
 */

#ifndef SCRIPTING_LUA_EXTRACTOR_H
#define	SCRIPTING_LUA_EXTRACTOR_H

#include "Scripting/Extractor.h"
#include "Scripting/typedefs.h"

extern "C"
{
#include <lua.h>
}

namespace Scripting
{
    namespace Lua
    {

        class Extractor : public Scripting::Extractor
        {
        public:
            Extractor(AnyVector& params, lua_State* const state);
            virtual ~Extractor();

            virtual void extract(const bool& b);
            virtual void extract(const long& i);
            virtual void extract(const double& d);

            virtual void extract(const char* s);
            virtual void extract(const String& s);

        private:
            lua_State* const state;
            int stackIndex;
        };
    }
}


#endif	/* SCRIPTING_LUA_EXTRACTOR_H */

