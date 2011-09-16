/* 
 * File:   TaskScheduler.h
 * Author: madrenegade
 *
 * Created on September 14, 2011, 5:16 PM
 */

#ifndef CORE_TASKSCHEDULER_H
#define	CORE_TASKSCHEDULER_H

#include <boost/shared_ptr.hpp>
#include <tbb/task.h>

namespace Utilities
{
    namespace Properties
    {
        class PropertyManager;
    }
}

namespace Core
{
    class Scene;
    
    class TaskScheduler
    {
    public:
        static void addOptionsTo(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
        
        TaskScheduler(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
        ~TaskScheduler();
        
        /**
         * Schedule the given task for executing in the background.
         * If you want to get notified when the task finished you should use events.
         */
        template<typename T>
        void scheduleBackgroundTask(const T& t)
        {
            backgroundTask->increment_ref_count();
            tbb::task& task = *new(backgroundTask->allocate_child()) T(t);
            backgroundTask->spawn(task);
        }
        
        /**
         * Execute the all tasks from the system scenes.
         */
        void executeTasks(Scene* scene);
        
    private:
        void startBackgroundTask();
        void waitForBackgroundTask();
        
        boost::shared_ptr<tbb::task_scheduler_init> tbbTaskScheduler;
        
        tbb::task_group_context backgroundTaskContext;
        tbb::task* backgroundTask;
        
        tbb::task_group_context taskContext;
        tbb::task* rootTask;
    };
}

#endif	/* CORE_TASKSCHEDULER_H */

