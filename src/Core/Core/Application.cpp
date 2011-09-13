/* 
 * File:   Application.cpp
 * Author: madrenegade
 * 
 * Created on September 13, 2011, 8:07 AM
 */

#include "Core/Application.h"

namespace Core
{

    Application::Application()
    {
        
    }

    Application::~Application()
    {
    }

    void Application::initialize()
    {
        onInitialize();
        
        onInitialized();
    }
    
    void Application::run()
    {
        onRun();
        
        while(onUpdate());
        
        onShutdown();
    }
   
    void Application::onInitialize()
    {
        
    }

    void Application::onInitialized()
    {
        
    }
    
    void Application::onRun()
    {
        
    }
    
    void Application::onShutdown()
    {
        
    }
    
}


