/* 
 * File:   SystemScene.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 2:35 PM
 */

#include "Graphics/SystemScene.h"

namespace Graphics
{

    SystemScene::SystemScene()
    {
    }

    SystemScene::~SystemScene()
    {
    }

    tbb::task* SystemScene::getTask(tbb::task* parent)
    {
        return new(parent->allocate_child()) tbb::empty_task;
    }
}
