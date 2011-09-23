/* 
 * File:   InputTask.h
 * Author: madrenegade
 *
 * Created on September 23, 2011, 8:15 AM
 */

#ifndef INPUT_INPUTTASK_H
#define	INPUT_INPUTTASK_H

#include <tbb/task.h>

namespace Input
{

    class InputTask : public tbb::task
    {
    public:
        InputTask();
        virtual ~InputTask();
        
        virtual tbb::task* execute();
    };
}

#endif	/* INPUT_INPUTTASK_H */

