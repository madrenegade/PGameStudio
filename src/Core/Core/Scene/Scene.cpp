/* 
 * File:   Scene.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 1:50 PM
 */

#include "Core/Scene/Scene.h"

namespace Core
{

    Scene::Scene()
    {
    }

    Scene::~Scene()
    {
    }
    
    void Scene::addSystemScene(const SystemScenePtr& scene)
    {
        systemScenes.push_front(scene);
    }
    
    Scene::SystemSceneList& Scene::getSystemScenes()
    {
        return systemScenes;
    }
}
