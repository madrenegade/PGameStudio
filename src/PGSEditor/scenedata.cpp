#include "scenedata.h"

void SceneData::mergeWith(const boost::shared_ptr<SceneData>& other)
{
    if(!rootNode)
    {
        rootNode = other->rootNode;
    }

    for(unsigned int i = 0; i < other->materials.size(); ++i)
    {
        materials.push_back(other->materials.at(i));
    }

    for(unsigned int i = 0; i < other->meshes.size(); ++i)
    {
        meshes.push_back(other->meshes.at(i));
    }

    for(unsigned int i = 0; i < other->cameras.size(); ++i)
    {
        cameras.push_back(other->cameras.at(i));
    }
}
