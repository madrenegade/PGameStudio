/* 
 * File:   OneAxisController.cpp
 * Author: madrenegade
 * 
 * Created on September 28, 2011, 9:16 AM
 */

#include "Input/OneAxisController.h"

namespace Input
{

    OneAxisController::OneAxisController()
    {
    }

    OneAxisController::~OneAxisController()
    {
    }
    
    double OneAxisController::getState() const
    {
        return state;
    }
}
