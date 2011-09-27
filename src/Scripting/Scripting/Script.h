/* 
 * File:   Script.h
 * Author: madrenegade
 *
 * Created on September 27, 2011, 1:00 PM
 */

#ifndef SCRIPTING_SCRIPT_H
#define	SCRIPTING_SCRIPT_H

namespace Scripting
{

    class Script
    {
    public:
        virtual ~Script();
        
        virtual void run() = 0;
        
    protected:
        Script();
    };
}

#endif	/* SCRIPTING_SCRIPT_H */

