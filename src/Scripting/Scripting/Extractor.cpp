/*
 * File:   Extractor.cpp
 * Author: madrenegade
 *
 * Created on September 15, 2011, 12:36 PM
 */

#include "Scripting/Extractor.h"

namespace Scripting
{
    Extractor::Extractor(AnyVector& params, lua_State* const state)
        : params(params), state(state), stackIndex(1)
    {
    }

    Extractor::~Extractor()
    {
    }

    void Extractor::operator()(const bool&)
    {
        if (!lua_isboolean(state, stackIndex))
        {
            LOG(FATAL) << "Expected parameter of type boolean as parameter " << stackIndex;
        }

        params.push_back(lua_toboolean(state, stackIndex) == 1);
        ++stackIndex;
    }

    void Extractor::operator()(const long&)
    {
        if (!lua_isnumber(state, stackIndex))
        {
            LOG(FATAL) << "Expected parameter of type integer as parameter " << stackIndex;
        }

        params.push_back(lua_tointeger(state, stackIndex));
        ++stackIndex;
    }

    void Extractor::operator()(const double&)
    {
        if (!lua_isnumber(state, stackIndex))
        {
            LOG(FATAL) << "Expected parameter of type double as parameter " << stackIndex;
        }

        params.push_back(lua_tonumber(state, stackIndex));
        ++stackIndex;
    }

    void Extractor::operator()(const char*)
    {
        if (!lua_isstring(state, stackIndex))
        {
            LOG(FATAL) << "Expected parameter of type string as parameter " << stackIndex;
        }

        params.push_back(lua_tostring(state, stackIndex));
        ++stackIndex;
    }

    void Extractor::operator()(const String&)
    {
        if (!lua_isstring(state, stackIndex))
        {
            LOG(FATAL) << "Expected parameter of type string as parameter " << stackIndex;
        }

        params.push_back(String(lua_tostring(state, stackIndex)));
        ++stackIndex;
    }
}


