/* 
 * File:   Application.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 8:07 AM
 */

#ifndef CORE_APPLICATION_H
#define	CORE_APPLICATION_H

namespace Core
{

    class Application
    {
    public:
        void initialize();
        void run();

    protected:
        Application();
        virtual ~Application();
        
        /**
         * called before initialization started
         */
        virtual void onInitialize();
        
        /**
         * called after initialization has been done
         */
        virtual void onInitialized();
        
        /**
         * called before the application is about to run
         */
        virtual void onRun();
        
        virtual bool onUpdate() = 0;
        
        virtual void onShutdown();
    };
}


#endif	/* CORE_APPLICATION_H */

