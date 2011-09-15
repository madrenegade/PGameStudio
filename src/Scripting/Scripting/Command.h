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

#include "Scripting/ScriptEngine.h"
#include "Scripting/Executor.h"
#include "Scripting/ExtractorProxy.h"

namespace Scripting
{

    class Command
    {
    public:
        Command(const char* name);

    private:
        std::string name;
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

        CommandT(const char* name, const boost::function<T>& fn)
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

        int execute(ScriptEngine* engine, Int2Type < true >) const
        {
            AnyVector params;

            boost::shared_ptr<Extractor> extractor = engine->createExtractor(params);
            boost::mpl::for_each<ParamTypes > (ExtractorProxy(extractor.get()));

            ExecutorType f;
            f(function, params);

            return 0;
        }

        // for non-void returns

        int execute(ScriptEngine* engine, Int2Type < false >) const
        {
            AnyVector params;

            boost::shared_ptr<Extractor> extractor = engine->createExtractor(params);
            boost::mpl::for_each<ParamTypes > (ExtractorProxy(extractor.get()));

            ExecutorType f;

            engine->setReturnValue(f(function, params));

            return 1;
        }

        static int callback(ScriptEngine* engine)
        {
            const CommandT<T>* this_ptr = reinterpret_cast<CommandT<T>*> (engine->getCommand());

            return this_ptr->execute(engine, Int2Type<IsVoidResult > ());
        }

    private:
        std::string name;
        boost::function<T> function;
    };
}

#endif	/* SCRIPTING_COMMAND_H */

