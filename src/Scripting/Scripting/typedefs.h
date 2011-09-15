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

namespace Scripting
{
    typedef std::vector<boost::any> AnyVector;
    
    template<int T> struct Int2Type {}; 
}

#endif	/* SCRIPTING_TYPEDEFS__H */

