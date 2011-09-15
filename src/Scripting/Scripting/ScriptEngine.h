/* 
 * File:   ScriptEngine.h
 * Author: madrenegade
 *
 * Created on September 14, 2011, 7:15 PM
 */

#ifndef SCRIPTING_SCRIPTENGINE_H
#define	SCRIPTING_SCRIPTENGINE_H

namespace Utilities
{
    namespace IO
    {
        class File;
    }
}

namespace Scripting
{

    class ScriptEngine
    {
    public:
        virtual ~ScriptEngine();
        
        virtual const char* getExtension() const = 0;
        
        virtual void runScript(const Utilities::IO::File& file) = 0;

    protected:
        ScriptEngine();
    };
}

#endif	/* SCRIPTING_SCRIPTENGINE_H */

