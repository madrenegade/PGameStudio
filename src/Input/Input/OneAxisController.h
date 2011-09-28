/* 
 * File:   OneAxisController.h
 * Author: madrenegade
 *
 * Created on September 28, 2011, 9:16 AM
 */

#ifndef INPUT_ONEAXISCONTROLLER_H
#define	INPUT_ONEAXISCONTROLLER_H

namespace Input
{

    class OneAxisController
    {
    public:
        OneAxisController();
        ~OneAxisController();
        
        /**
         * Get the state of the axis
         * @return 0 - unpressed
         * 1 - fully pressed
         * (0...1) - partially pressed
         */
        double getState() const;
        
    private:
        double state;
    };
}

#endif	/* INPUT_ONEAXISCONTROLLER_H */

