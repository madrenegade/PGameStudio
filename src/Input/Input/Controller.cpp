/*
 * File:   Controller.cpp
 * Author: madrenegade
 *
 * Created on September 28, 2011, 11:39 AM
 */

#include "Input/Controller.h"
#include "Input/Button.h"
#include "Input/OneAxisControl.h"
#include "Input/TwoAxisControl.h"

namespace Input
{

    Controller::Controller(const String& id)
    : id(id)
    {
    }

    Controller::~Controller()
    {
    }

    const String& Controller::getID() const
    {
        return id;
    }

    void Controller::registerButton(const unsigned int keysym, const char* const var)
    {
        if(buttons.find(keysym) != buttons.end())
        {
            LOG(FATAL) << "A button is already registered for the keysym " << keysym;
        }

        buttons[keysym].reset(new Button(var));
    }

    void Controller::registerOneAxisControl(const unsigned int controlID, const char* const var, const char* const deltaVar)
    {
        if(oneAxisControls.find(controlID) != oneAxisControls.end())
        {
            LOG(FATAL) << "A one-axis-control is already registered for the control id " << controlID;
        }

        oneAxisControls[controlID].reset(new OneAxisControl(var, deltaVar));
    }

    void Controller::registerTwoAxisControl(const unsigned int controlID, const char* const xVar, const char* const yVar,
                                            const char* const xDeltaVar, const char* const yDeltaVar)
    {
        if(twoAxisControls.find(controlID) != twoAxisControls.end())
        {
            LOG(FATAL) << "A two-axis-control is already registered for the control id " << controlID;
        }

        twoAxisControls[controlID].reset(new TwoAxisControl(xVar, yVar, xDeltaVar, yDeltaVar));
    }

    Button* Controller::getButtonFor(const unsigned int keysym)
    {
        return buttons[keysym].get();
    }

    OneAxisControl* Controller::getOneAxisControl(const unsigned int id)
    {
        return oneAxisControls[id].get();
    }

    TwoAxisControl* Controller::getTwoAxisControl(const unsigned int id)
    {
        return twoAxisControls[id].get();
    }
}
