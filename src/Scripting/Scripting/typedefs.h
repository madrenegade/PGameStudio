/*
 * File:   typedefs..h
 * Author: madrenegade
 *
 * Created on September 15, 2011, 9:29 AM
 */

#ifndef SCRIPTING_TYPEDEFS__H
#define	SCRIPTING_TYPEDEFS__H

#include <vector>
#include <boost/any.hpp>
#include "Utilities/Memory/STLAllocator.h"

namespace Scripting
{
    class Command;
    class ScriptEngine;

    typedef std::vector<boost::any> AnyVector;

    template<int T> struct Int2Type {};

    typedef boost::shared_ptr<Command> CommandPtr;
    typedef std::pair<CommandPtr, int (*)(ScriptEngine*)> CommandCallback;
    typedef std::vector<CommandCallback, Utilities::Memory::STLAllocator<CommandCallback>> CommandCallbacks;
}

#endif	/* SCRIPTING_TYPEDEFS__H */

