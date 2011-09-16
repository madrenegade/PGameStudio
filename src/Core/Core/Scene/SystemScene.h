/* 
 * File:   SystemScene.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 2:28 PM
 */

#ifndef CORE_SYSTEMSCENE_H
#define	CORE_SYSTEMSCENE_H

#include <tbb/task.h>

namespace Core
{

    class SystemScene
    {
    public:
        virtual ~SystemScene();

        // void setMemoryManager()

        virtual tbb::task* getTask(tbb::task* parent) = 0;

    protected:
        SystemScene();
    };
}

#endif	/* CORE_SYSTEMSCENE_H */

