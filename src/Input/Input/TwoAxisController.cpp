/* 
 * File:   TwoAxisController.cpp
 * Author: madrenegade
 * 
 * Created on September 28, 2011, 9:17 AM
 */

#include "Input/TwoAxisController.h"

namespace Input
{

    TwoAxisController::TwoAxisController()
    {
    }

    TwoAxisController::~TwoAxisController()
    {
    }
    
    void TwoAxisController::getState(double& x, double& y) const
    {
        x = this->x;
        y = this->y;
    }
}
