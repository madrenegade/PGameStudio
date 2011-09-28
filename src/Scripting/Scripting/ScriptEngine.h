/* 
 * File:   ScriptEngine.h
 * Author: madrenegade
 *
 * Created on September 14, 2011, 7:15 PM
 */

#ifndef SCRIPTING_SCRIPTENGINE_H
#define	SCRIPTING_SCRIPTENGINE_H

#include <boost/shared_ptr.hpp>

#include "Scripting/typedefs.h"
#include "Utilities/string.h"

namespace Utilities
{
    namespace IO
    {
        class File;
    }
}

namespace Scripting
{
    class Extractor;
    class Command;
    class Script;
    
    class ScriptEngine
    {
    public:
        virtual ~ScriptEngine();
        
        virtual const char* getExtension() const = 0;
        
        /**
         * Load a script.
         * @param file - the data of the script
         * @param name - the name of the script
         * @return 
         */
        virtual boost::shared_ptr<Script> load(const Utilities::IO::File& file, const char* name) = 0;
        
        /**
         * Create an extractor.
         * @param params - the vector to push extracted params to
         * @return 
         */
        virtual boost::shared_ptr<Extractor> createExtractor(AnyVector& params) const = 0;
        
        /**
         * Get the command for the function which is about to execute.
         * @return 
         */
        virtual Command* getCommand() const = 0;
        
        /**
         * Register a function and make it accessible to scripts.
         * @param name - the name used to call the function from scripts
         * @param cmd - the command which belongs to the function
         * @param fn - the callback function
         */
        virtual void registerFunction(const char* name, Command* cmd, int (*fn)(ScriptEngine*)) = 0;
        
        /**
         * Set the return value for the currently executed function.
         * @param b
         */
        virtual void setReturnValue(const bool& b) = 0;
        virtual void setReturnValue(const long& i) = 0;
        virtual void setReturnValue(const double& d) = 0;
        virtual void setReturnValue(const String& s) = 0;
        
        virtual void setVariable(const char* const name, const bool& value) = 0;

    protected:
        ScriptEngine();
    };
}

#endif	/* SCRIPTING_SCRIPTENGINE_H */

