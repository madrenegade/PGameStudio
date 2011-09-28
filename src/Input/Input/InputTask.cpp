/* 
 * File:   InputTask.cpp
 * Author: madrenegade
 * 
 * Created on September 23, 2011, 8:15 AM
 */

#include "Input/InputTask.h"
#include "Input/Button.h"

#include "Core/Events/EventManager.h"

namespace Input
{

    InputTask::InputTask(Core::Events::EventManager* eventManager,
        std::vector<Button*, Utilities::Memory::STLAllocator<Button*>>& dirtyButtons)
    : eventManager(eventManager), dirtyButtons(dirtyButtons)
    {
    }

    InputTask::~InputTask()
    {
    }

    tbb::task* InputTask::execute()
    {
        processDirtyButtons();
        return 0;
    }
    
    void InputTask::processDirtyButtons()
    {
        for(auto i = dirtyButtons.begin(); i != dirtyButtons.end(); ++i)
        {
            eventManager->pushEvent((*i)->getEvent(), (*i)->isPressed());
        }
        
        dirtyButtons.clear();
    }
}