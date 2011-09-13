/* 
 * File:   Library.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 11:20 AM
 */

#ifndef PLATFORM_LIBRARY_H
#define	PLATFORM_LIBRARY_H

#ifdef LINUX
#include "Platform/Linux/Library.h"
#else 
#error "Only linux shared objects are supported at the moment"
#endif

#endif	/* PLATFORM_LIBRARY_H */

