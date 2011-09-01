/* 
 * File:   functions.h
 * Author: madrenegade
 *
 * Created on September 1, 2011, 3:01 PM
 */

#ifndef UTILITIES_FUNCTIONS_H
#define	UTILITIES_FUNCTIONS_H

#include <string>

namespace Utilities
{
    /**
     * uses compiler specific api to demangle type and function names
     * @param name
     * @return 
     */
    std::string demangle(const char* name);
}

#endif	/* UTILITIES_FUNCTIONS_H */

