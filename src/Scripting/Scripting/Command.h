/*
 * File:   Command.h
 * Author: madrenegade
 *
 * Created on September 15, 2011, 12:13 PM
 */

#ifndef SCRIPTING_COMMAND_H
#define	SCRIPTING_COMMAND_H

#include <boost/function.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

#include "Scripting/Engine.h"
#include "Scripting/Executor.h"
#include "Scripting/Extractor.h"

namespace Scripting
{
    void setReturnValue(lua_State* const state, const bool& b);
    void setReturnValue(lua_State* const state, const long& i);
    void setReturnValue(lua_State* const state, const double& d);
    void setReturnValue(lua_State* const state, const String& s);

    class Command
    {
    public:
        Command(const char* const name);

        const char* getName() const
        {
            return name.c_str();
        }

    private:
        String name;
    };

    struct remove_ref
    {
        template <class T>
        struct apply
        {
            typedef typename boost::remove_reference<T>::type type;
        };
    };

    template<typename T>
    class CommandT : public Command
    {
    public:
        CommandT(const char* const name, const boost::function<T>& fn)
            : Command(name), function(fn)
        {

        }

        // Remove the references from the parameter types
        typedef typename boost::mpl::transform< boost::function_types::parameter_types<T>, remove_ref>::type ParamTypes;

        typedef typename boost::function_types::result_type<T>::type ResultType;

        enum
        {
            IsVoidResult = boost::is_void<ResultType>::value
        };

        typedef Executor<Int2Type<boost::function_types::function_arity<T>::value>, ParamTypes, ResultType > ExecutorType;

        // for void returns
        int execute(lua_State* state, Int2Type<true>) const
        {
            AnyVector params;

            boost::mpl::for_each<ParamTypes > (Extractor(params, state));

            ExecutorType executor;
            executor(function, params);

            return 0;
        }

        // for non-void returns
        int execute(lua_State* state, Int2Type<false>) const
        {
            AnyVector params;

            boost::mpl::for_each<ParamTypes > (Extractor(params, state));

            ExecutorType executor;
            setReturnValue(state, executor(function, params));

            return 1;
        }

        static int callback(Engine* engine)
        {
            const CommandT<T>* this_ptr = reinterpret_cast<CommandT<T>*> (engine->getCommand());

            return this_ptr->execute(engine, Int2Type<IsVoidResult > ());
        }

    private:
        boost::function<T> function;
    };
}

#endif	/* SCRIPTING_COMMAND_H */

