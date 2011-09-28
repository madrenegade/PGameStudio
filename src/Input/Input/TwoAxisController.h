/* 
 * File:   TwoAxisController.h
 * Author: madrenegade
 *
 * Created on September 28, 2011, 9:17 AM
 */

#ifndef INPUT_TWOAXISCONTROLLER_H
#define	INPUT_TWOAXISCONTROLLER_H

namespace Input
{

    class TwoAxisController
    {
    public:
        TwoAxisController();
        ~TwoAxisController();
        
        /**
         * Retreive the state of the controller. The values are in the range
         * [-1...1] with 0 representing the "center".
         * @param x - the variable to store the x-value in
         * @param y - the variable to store the y-value in
         */
        void getState(double& x, double& y) const;
        
    private:
        double x;
        double y;
    };
}

#endif	/* INPUT_TWOAXISCONTROLLER_H */

