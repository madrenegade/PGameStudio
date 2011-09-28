/* 
 * File:   TwoAxisController.h
 * Author: madrenegade
 *
 * Created on September 28, 2011, 9:17 AM
 */

#ifndef INPUT_TWOAXISCONTROL_H
#define	INPUT_TWOAXISCONTROL_H

#include "Utilities/string.h"

namespace Input
{

    class TwoAxisControl
    {
    public:
        TwoAxisControl(const char* const xVar, const char* const yVar);
        ~TwoAxisControl();
        
        /**
         * Retreive the state of the controller. The values are in the range
         * [-1...1] with 0 representing the "center".
         * @param x - the variable to store the x-value in
         * @param y - the variable to store the y-value in
         */
        void getState(double& x, double& y) const;
        void getDelta(double& x, double& y) const;
        
        void setState(double x, double y);
        
        const char* const getXVariableName() const;
        const char* const getYVariableName() const;
        
    private:
        String xVar;
        String yVar;
        
        double x;
        double y;
        
        double deltaX;
        double deltaY;
    };
}

#endif	/* INPUT_TWOAXISCONTROL_H */

