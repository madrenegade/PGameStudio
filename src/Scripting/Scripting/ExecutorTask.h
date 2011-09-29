/*
 * File:   ExecutorTask.h
 * Author: madrenegade
 *
 * Created on September 27, 2011, 2:05 PM
 */

#ifndef SCRIPTING_EXECUTORTASK_H
#define	SCRIPTING_EXECUTORTASK_H

#include <tbb/task.h>

namespace Scripting
{
    class ScriptManager;

    class ExecutorTask : public tbb::task
    {
    public:
        ExecutorTask(ScriptManager* const scriptManager);
        virtual ~ExecutorTask();

        virtual tbb::task* execute();

    private:
        ScriptManager* const scriptManager;
    };
}

#endif	/* SCRIPTING_EXECUTORTASK_H */

