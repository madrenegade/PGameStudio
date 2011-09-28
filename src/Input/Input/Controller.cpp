/* 
 * File:   Controller.cpp
 * Author: madrenegade
 * 
 * Created on September 28, 2011, 11:39 AM
 */

#include "Input/Controller.h"

namespace Input
{

    Controller::Controller(const String& id)
    : id(id)
    {
    }

    Controller::~Controller()
    {
    }
    
    const String& Controller::getID() const
    {
        return id;
    }
    
    void Controller::registerButton(const unsigned int keysym, const Core::Events::EventID& event)
    {
        // TODO: check that button is not already registered
        buttons[keysym].reset(new Button(event));
    }
    
    Button* Controller::getButtonFor(const unsigned int keysym)
    {
        return buttons[keysym].get();
    }
}
