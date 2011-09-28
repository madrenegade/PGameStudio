/* 
 * File:   Button.h
 * Author: madrenegade
 *
 * Created on September 28, 2011, 9:16 AM
 */

#ifndef INPUT_BUTTON_H
#define	INPUT_BUTTON_H

namespace Input
{

    class Button
    {
    public:
        Button();
        ~Button();
        
        /**
         * 
         * @return true if the button is not pressed at all.
         */
        bool isUp() const;
        
        /**
         * 
         * @return true if the button is pressed.
         */
        bool isDown() const;
        
    private:
        bool isPressed;
    };
}

#endif	/* INPUT_BUTTON_H */

