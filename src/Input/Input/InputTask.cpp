/*
 * File:   InputTask.cpp
 * Author: madrenegade
 *
 * Created on September 23, 2011, 8:15 AM
 */

#include "Input/InputTask.h"
#include "Input/Button.h"
#include "Input/OneAxisControl.h"
#include "Input/TwoAxisControl.h"

#include "Core/Events/EventManager.h"

namespace Input
{

    InputTask::InputTask(Core::Events::EventManager* eventManager,
                         const Core::Events::EventID& event,
                         std::vector<Button*, Utilities::Memory::STLAllocator<Button*>>& dirtyButtons,
                         std::vector<OneAxisControl*, Utilities::Memory::STLAllocator<OneAxisControl*>>& dirtyOneAxisControls,
                         std::vector<TwoAxisControl*, Utilities::Memory::STLAllocator<TwoAxisControl*>>& dirtyTwoAxisControls)
        : eventManager(eventManager), event(event),
          dirtyButtons(dirtyButtons), dirtyOneAxisControls(dirtyOneAxisControls),
          dirtyTwoAxisControls(dirtyTwoAxisControls)
    {
    }

    InputTask::~InputTask()
    {
    }

    tbb::task* InputTask::execute()
    {
        processDirtyButtons();
        processDirtyOneAxisControls();
        processDirtyTwoAxisControls();

        return 0;
    }

    void InputTask::processDirtyButtons()
    {
        for (auto i = dirtyButtons.begin(); i != dirtyButtons.end(); ++i)
        {
            eventManager->pushEvent(event, std::make_pair((*i)->getVariableName(), (*i)->isPressed()));
        }

        dirtyButtons.clear();
    }

    void InputTask::processDirtyOneAxisControls()
    {
        for(auto i = dirtyOneAxisControls.begin(); i != dirtyOneAxisControls.end(); ++i)
        {
            eventManager->pushEvent(event, std::make_pair((*i)->getVariableName(), (*i)->getState()));
            eventManager->pushEvent(event, std::make_pair((*i)->getDeltaVariableName(), (*i)->getDelta()));
        }

        dirtyOneAxisControls.clear();
    }

    void InputTask::processDirtyTwoAxisControls()
    {
        double x, y;
        double deltaX, deltaY;

        for(auto i = dirtyTwoAxisControls.begin(); i != dirtyTwoAxisControls.end(); ++i)
        {
            (*i)->getState(x, y);
            (*i)->getDelta(deltaX, deltaY);

            eventManager->pushEvent(event, std::make_pair((*i)->getXVariableName(), x));
            eventManager->pushEvent(event, std::make_pair((*i)->getYVariableName(), y));
            eventManager->pushEvent(event, std::make_pair((*i)->getDeltaXVariableName(), deltaX));
            eventManager->pushEvent(event, std::make_pair((*i)->getDeltaYVariableName(), deltaY));
        }

        dirtyTwoAxisControls.clear();
    }
}
