/* 
 * File:   OneAxisController.h
 * Author: madrenegade
 *
 * Created on September 28, 2011, 9:16 AM
 */

#ifndef INPUT_ONEAXISCONTROL_H
#define	INPUT_ONEAXISCONTROL_H

#include "Utilities/string.h"

namespace Input
{

    class OneAxisControl
    {
    public:
        OneAxisControl(const char* const var, const char* const deltaVar);
        ~OneAxisControl();
        
        /**
         * Get the state of the axis
         * @return 0 - unpressed
         * 1 - fully pressed
         * (0...1) - partially pressed
         */
        double getState() const;
        
        /**
         * Get the difference to the last set value
         * @return 
         */
        double getDelta() const;
        
        void setState(double x);
        
        const char* getVariableName() const;
        const char* getDeltaVariableName() const;
        
    private:
        String var;
        String deltaVar;
        
        double state;
        double delta;
    };
}

#endif	/* INPUT_ONEAXISCONTROL_H */

