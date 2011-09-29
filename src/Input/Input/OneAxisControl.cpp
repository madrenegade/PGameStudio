/* 
 * File:   OneAxisController.cpp
 * Author: madrenegade
 * 
 * Created on September 28, 2011, 9:16 AM
 */

#include "Input/OneAxisControl.h"

namespace Input
{

    OneAxisControl::OneAxisControl(const char* const var, const char* const deltaVar)
    : var(var), deltaVar(deltaVar), state(0), delta(0)
    {
    }

    OneAxisControl::~OneAxisControl()
    {
    }
    
    double OneAxisControl::getState() const
    {
        return state;
    }
    
    double OneAxisControl::getDelta() const
    {
        return delta;
    }
    
    void OneAxisControl::setState(double x)
    {
        delta = x - state;
        state = x;
    }
    
    const char* OneAxisControl::getVariableName() const
    {
        return var.c_str();
    }
    
    const char* OneAxisControl::getDeltaVariableName() const
    {
        return deltaVar.c_str();
    }
}
