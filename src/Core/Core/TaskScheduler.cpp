/* 
 * File:   TaskScheduler.cpp
 * Author: madrenegade
 * 
 * Created on September 14, 2011, 5:16 PM
 */

#include "Core/TaskScheduler.h"
#include "Utilities/Properties/PropertyManager.h"

#include <tbb/task.h>
#include <tbb/task_scheduler_init.h>

#include <glog/logging.h>

using namespace Utilities::Properties;

namespace Core
{

    void TaskScheduler::addOptionsTo(const PropertyManager::Ptr& properties)
    {
        po::options_description options("Task scheduler options");

        options.add_options()
            ("Scheduler.numThreads", po::value<unsigned int>()->default_value(0), "The number of threads to use");

        properties->addOptions(options);
    }

    TaskScheduler::TaskScheduler(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties)
    : backgroundTask(0), rootTask(0)
    {
        unsigned int numThreads = properties->get<unsigned int>("Scheduler.numThreads");

        if (numThreads == 0)
        {
            numThreads = tbb::task_scheduler_init::default_num_threads();
        }
        
        VLOG(1) << "Task scheduler uses " << numThreads << " threads";

        tbbTaskScheduler.reset(new tbb::task_scheduler_init(numThreads));
        
        backgroundTaskContext.set_priority(tbb::priority_low);
        taskContext.set_priority(tbb::priority_normal);
        
        startBackgroundTask();
    }

    TaskScheduler::~TaskScheduler()
    {
        waitForBackgroundTask();
    }

    void TaskScheduler::executeTasks(tbb::task_list& tasks, unsigned int numTasks)
    {
        rootTask = new(tbb::task::allocate_root(taskContext)) tbb::empty_task;

        rootTask->set_ref_count(numTasks + 1);
        rootTask->spawn_and_wait_for_all(tasks);
        rootTask->destroy(*rootTask);
    }
    
    void TaskScheduler::startBackgroundTask()
    {
        backgroundTask = new(tbb::task::allocate_root(backgroundTaskContext)) tbb::empty_task;
        backgroundTask->set_ref_count(1);
    }
    
    void TaskScheduler::waitForBackgroundTask()
    {
        VLOG(1) << "Waiting for background tasks to finish...";
        
        backgroundTask->wait_for_all();
        backgroundTask->destroy(*backgroundTask);
        
        VLOG(1) << "Background tasks finished";
    }
}
