/* 
 * File:   Button.cpp
 * Author: madrenegade
 * 
 * Created on September 28, 2011, 9:16 AM
 */

#include "Input/Button.h"

namespace Input
{

    Button::Button(const Core::Events::EventID& event)
    : event(event), m_isPressed(false)
    {
    }

    Button::~Button()
    {
    }

    bool Button::isPressed() const
    {
        return m_isPressed;
    }

    void Button::setState(bool pressed)
    {
        m_isPressed = pressed;
    }

    const Core::Events::EventID& Button::getEvent() const
    {
        return event;
    }
}
