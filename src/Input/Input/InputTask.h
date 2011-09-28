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
#include "Core/Events/typedefs.h"

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
    class OneAxisControl;
    class TwoAxisControl;
    
    class InputTask : public tbb::task
    {
    public:
        InputTask(Core::Events::EventManager* eventManager, 
                  const Core::Events::EventID& event, 
                  std::vector<Button*, Utilities::Memory::STLAllocator<Button*>>& dirtyButtons,
                  std::vector<OneAxisControl*, Utilities::Memory::STLAllocator<OneAxisControl*>>& dirtyOneAxisControls,
                  std::vector<TwoAxisControl*, Utilities::Memory::STLAllocator<TwoAxisControl*>>& dirtyTwoAxisControls);
        virtual ~InputTask();
        
        virtual tbb::task* execute();
        
    private:
        void processDirtyButtons();
        void processDirtyOneAxisControls();
        void processDirtyTwoAxisControls();
        
        Core::Events::EventManager* eventManager;
        const Core::Events::EventID event;
        
        std::vector<Button*, Utilities::Memory::STLAllocator<Button*>>& dirtyButtons;
        std::vector<OneAxisControl*, Utilities::Memory::STLAllocator<OneAxisControl*>>& dirtyOneAxisControls;
        std::vector<TwoAxisControl*, Utilities::Memory::STLAllocator<TwoAxisControl*>>& dirtyTwoAxisControls;
    };
}

#endif	/* INPUT_INPUTTASK_H */

