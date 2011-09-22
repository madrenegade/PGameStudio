/* 
 * File:   Extractor.cpp
 * Author: madrenegade
 * 
 * Created on September 15, 2011, 12:36 PM
 */

#include "Scripting/Lua/Extractor.h"

namespace Scripting
{
    namespace Lua
    {

        Extractor::Extractor(AnyVector& params, lua_State* state)
        : Scripting::Extractor(params), state(state), stackIndex(1)
        {
        }

        Extractor::~Extractor()
        {
        }
        
        void Extractor::extract(const bool& b)
        {
            if (!lua_isboolean(state, stackIndex))
            {
                LOG(FATAL) << "Expected parameter of type boolean as parameter " << stackIndex;
            }

            params.push_back(lua_toboolean(state, stackIndex) == 1);
            ++stackIndex;
        }

        void Extractor::extract(const long& i)
        {
            if (!lua_isnumber(state, stackIndex))
            {
                LOG(FATAL) << "Expected parameter of type integer as parameter " << stackIndex;
            }

            params.push_back(lua_tointeger(state, stackIndex));
            ++stackIndex;
        }
        
        void Extractor::extract(const double& d)
        {
            if (!lua_isnumber(state, stackIndex))
            {
                LOG(FATAL) << "Expected parameter of type double as parameter " << stackIndex;
            }

            params.push_back(lua_tonumber(state, stackIndex));
            ++stackIndex;
        }
        
        void Extractor::extract(const char* s)
        {
            if (!lua_isstring(state, stackIndex))
            {
                LOG(FATAL) << "Expected parameter of type string as parameter " << stackIndex;
            }
            
            params.push_back(lua_tostring(state, stackIndex));
            ++stackIndex;
        }

        void Extractor::extract(const String& s)
        {
            if (!lua_isstring(state, stackIndex))
            {
                LOG(FATAL) << "Expected parameter of type string as parameter " << stackIndex;
            }
            
            params.push_back(String(lua_tostring(state, stackIndex)));
            ++stackIndex;
        }
    }
}


