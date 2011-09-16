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
    class Renderer;
    
    class SystemScene : public Core::SystemScene
    {
    public:
        SystemScene();
        virtual ~SystemScene();
        
        virtual void initialize();
        
        virtual const char* getSceneFileExtension() const;
        
        virtual void load(const Utilities::IO::File& file);
        
        virtual tbb::task* getTask(tbb::task* parent);
        
    private:
        static const std::string SCENE_FILE_EXTENSION;
        
        boost::shared_ptr<Renderer> renderer;
    };
}

#endif	/* GRAPHICS_SYSTEMSCENE_H */

