/* 
 * File:   Application.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 8:07 AM
 */

#ifndef GAME_APPLICATION_H
#define	GAME_APPLICATION_H

#include "Core/Application.h"

namespace Game
{

    class Application : public Core::Application
    {
    public:
        Application();
        virtual ~Application();
        
    protected:
        virtual bool onUpdate();
    };
}


#endif	/* GAME_APPLICATION_H */

