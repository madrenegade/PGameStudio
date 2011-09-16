/* 
 * File:   SystemScene.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 2:35 PM
 */

#ifndef GRAPHICS_SYSTEMSCENE_H
#define	GRAPHICS_SYSTEMSCENE_H

#include "Core/Scene/SystemScene.h"

namespace Graphics
{

    class SystemScene : public Core::SystemScene
    {
    public:
        SystemScene();
        virtual ~SystemScene();
        
        virtual tbb::task* getTask(tbb::task* parent);
    };
}

#endif	/* GRAPHICS_SYSTEMSCENE_H */

