/*
 * File:   TwoAxisController.cpp
 * Author: madrenegade
 *
 * Created on September 28, 2011, 9:17 AM
 */

#include "Input/TwoAxisControl.h"

namespace Input
{

    TwoAxisControl::TwoAxisControl(const char* const xVar, const char* const yVar,
                                   const char* const xDeltaVar, const char* const yDeltaVar)
        : xVar(xVar), yVar(yVar), xDeltaVar(xDeltaVar), yDeltaVar(yDeltaVar), x(0), y(0), deltaX(0), deltaY(0)
    {
    }

    TwoAxisControl::~TwoAxisControl()
    {
    }

    void TwoAxisControl::getState(double& x, double& y) const
    {
        x = this->x;
        y = this->y;
    }

    void TwoAxisControl::getDelta(double& x, double& y) const
    {
        x = deltaX;
        y = deltaY;
    }

    void TwoAxisControl::setState(double x, double y)
    {
        deltaX = x - this->x;
        deltaY = y - this->y;

        this->x = x;
        this->y = y;
    }

    void TwoAxisControl::center()
    {
        deltaX = 0;
        deltaY = 0;
        x = 0;
        y = 0;
    }

    const char* TwoAxisControl::getXVariableName() const
    {
        return xVar.c_str();
    }

    const char* TwoAxisControl::getYVariableName() const
    {
        return yVar.c_str();
    }

    const char* TwoAxisControl::getDeltaXVariableName() const
    {
        return xDeltaVar.c_str();
    }

    const char* TwoAxisControl::getDeltaYVariableName() const
    {
        return yDeltaVar.c_str();
    }
}
