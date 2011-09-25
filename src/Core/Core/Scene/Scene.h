/* 
 * File:   Scene.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 1:50 PM
 */

#ifndef CORE_SCENE_H
#define	CORE_SCENE_H

#include "Utilities/Memory/STLAllocator.h"

namespace Core
{
    class SystemScene;
    
    class Scene
    {
    public:
        typedef boost::shared_ptr<SystemScene> SystemScenePtr;
        typedef std::list<SystemScenePtr, Utilities::Memory::STLAllocator<SystemScenePtr>> SystemSceneList;
        
        Scene();
        ~Scene();
        
        void addSystemScene(const SystemScenePtr& scene);
        
        const SystemSceneList& getSystemScenes() const;
        
    private:
        SystemSceneList systemScenes;
    };
}

#endif	/* CORE_SCENE_H */

