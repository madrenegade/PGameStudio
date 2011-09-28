/* 
 * File:   ExecutorTask.cpp
 * Author: madrenegade
 * 
 * Created on September 27, 2011, 2:05 PM
 */

#include "Scripting/ExecutorTask.h"
#include "ScriptManager.h"

namespace Scripting
{

    ExecutorTask::ExecutorTask(ScriptManager* scriptManager)
    : scriptManager(scriptManager)
    {
    }

    ExecutorTask::~ExecutorTask()
    {
    }

    tbb::task* ExecutorTask::execute()
    {
        scriptManager->runScript("update");
        scriptManager->runGarbageCollection();
        
        return 0;
    }
}
