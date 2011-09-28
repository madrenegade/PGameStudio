/* 
 * File:   Button.cpp
 * Author: madrenegade
 * 
 * Created on September 28, 2011, 9:16 AM
 */

#include "Input/Button.h"

namespace Input
{

    Button::Button()
    {
    }

    Button::~Button()
    {
    }
    
    bool Button::isUp() const
    {
        return !isPressed;
    }
    
    bool Button::isDown() const
    {
        return isPressed;
    }
}
