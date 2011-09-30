/*
 * File:   Executor.h
 * Author: madrenegade
 *
 * Created on September 15, 2011, 12:29 PM
 */

#ifndef SCRIPTING_EXECUTOR_H
#define	SCRIPTING_EXECUTOR_H

#include "Scripting/typedefs.h"
#include <boost/mpl/at.hpp>

#include <glog/logging.h>

namespace Scripting
{
    template<class arity, class ParamTypes, class ResultType>
    struct Executor;

    // 0 parameters
    template<class ParamTypes, class ResultType>
    struct Executor<Int2Type<0>, ParamTypes, ResultType>
    {

        template<class Fn>
        ResultType operator()(Fn& fn, const AnyVector&)
        {
            return fn();
        }

//        template<class ObjType, class MemFn>
//        ResultType operator()(Obj& obj, MemFn& mem_fn, const AnyParams&)
//        {
//            return (obj->*mem_fn)();
//        }
    };

    // 1 parameter
    template<class ParamTypes, typename ResultType>
    struct Executor<Int2Type<1>, ParamTypes, ResultType>
    {

        template<class Fn>
        ResultType operator()(Fn& fn, const AnyVector& params)
        {
            typedef typename boost::mpl::at<ParamTypes, boost::mpl::int_ < 0 > >::type typeOfParam0;

            return fn(boost::any_cast<typeOfParam0 > (params[0]));
        }
    };

    // 2 parameters
    template<class ParamTypes, typename ResultType>
    struct Executor<Int2Type<2>, ParamTypes, ResultType>
    {

        template<class Fn>
        ResultType operator()(Fn& fn, const AnyVector& params)
        {
            typedef typename boost::mpl::at<ParamTypes, boost::mpl::int_ < 0 > >::type typeOfParam0;
            typedef typename boost::mpl::at<ParamTypes, boost::mpl::int_ < 1 > >::type typeOfParam1;

            return fn(boost::any_cast<typeOfParam0 > (params[0]),
                      boost::any_cast<typeOfParam1 > (params[1]));
        }
    };

    // 3 parameters
    template<class ParamTypes, typename ResultType>
    struct Executor< Int2Type < 3 >, ParamTypes, ResultType >
    {

        template<class Fn >
        ResultType operator()(Fn& fn, const AnyVector& params)
        {
            typedef typename boost::mpl::at<ParamTypes, boost::mpl::int_ < 0 > >::type typeOfParam0;
            typedef typename boost::mpl::at<ParamTypes, boost::mpl::int_ < 1 > >::type typeOfParam1;
            typedef typename boost::mpl::at<ParamTypes, boost::mpl::int_ < 2 > >::type typeOfParam2;

            return fn(boost::any_cast< typeOfParam0 > (params[0]),
                      boost::any_cast< typeOfParam1 > (params[1]),
                      boost::any_cast< typeOfParam2 > (params[2]));
        }
    };

    // 4 parameters
    template<class ParamTypes, typename ResultType>
    struct Executor< Int2Type < 4 >, ParamTypes, ResultType >
    {

        template<class Fn >
        ResultType operator()(Fn& fn, const AnyVector& params)
        {
            typedef typename boost::mpl::at<ParamTypes, boost::mpl::int_ < 0 > >::type typeOfParam0;
            typedef typename boost::mpl::at<ParamTypes, boost::mpl::int_ < 1 > >::type typeOfParam1;
            typedef typename boost::mpl::at<ParamTypes, boost::mpl::int_ < 2 > >::type typeOfParam2;
            typedef typename boost::mpl::at<ParamTypes, boost::mpl::int_ < 3 > >::type typeOfParam3;

            return fn(boost::any_cast< typeOfParam0 > (params[0]),
                      boost::any_cast< typeOfParam1 > (params[1]),
                      boost::any_cast< typeOfParam2 > (params[2]),
                      boost::any_cast< typeOfParam2 > (params[3]));
        }
    };
}

#endif	/* SCRIPTING_EXECUTOR_H */

