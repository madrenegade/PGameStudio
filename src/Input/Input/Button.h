/* 
 * File:   Button.h
 * Author: madrenegade
 *
 * Created on September 28, 2011, 9:16 AM
 */

#ifndef INPUT_BUTTON_H
#define	INPUT_BUTTON_H

#include "Utilities/string.h"

namespace Input
{

    class Button
    {
    public:
        Button(const char* const var);
        ~Button();
        
        /**
         * 
         * @return true if the button is pressed.
         */
        bool isPressed() const;
        
        /**
         * Set the button state.
         * @param pressed - true if button is pressed, false otherwise
         */
        void setState(bool pressed);
        
        const char* const getVariableName() const;
        
    private:
        String var;
        
        bool m_isPressed;
    };
}

#endif	/* INPUT_BUTTON_H */

