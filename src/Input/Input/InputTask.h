/* 
 * File:   InputTask.h
 * Author: madrenegade
 *
 * Created on September 23, 2011, 8:15 AM
 */

#ifndef INPUT_INPUTTASK_H
#define	INPUT_INPUTTASK_H

#include <tbb/task.h>
#include <vector>

#include "Utilities/Memory/STLAllocator.h"

namespace Core
{
    namespace Events
    {
        class EventManager;
    }
}

namespace Input
{
    class Button;
    
    class InputTask : public tbb::task
    {
    public:
        InputTask(Core::Events::EventManager* eventManager, std::vector<Button*, Utilities::Memory::STLAllocator<Button*>>& dirtyButtons);
        virtual ~InputTask();
        
        virtual tbb::task* execute();
        
    private:
        void processDirtyButtons();
        
        Core::Events::EventManager* eventManager;
        std::vector<Button*, Utilities::Memory::STLAllocator<Button*>>& dirtyButtons;
    };
}

#endif	/* INPUT_INPUTTASK_H */

