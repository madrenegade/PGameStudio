#include "scenedata.h"

SceneData::SceneData()
{
}

void SceneData::mergeWith(const boost::shared_ptr<SceneData>& other)
{
    if(!rootNode)
    {
        rootNode = other->rootNode;
    }

    for(unsigned int i = 0; i < other->meshes.size(); ++i)
    {
        meshes.push_back(other->meshes.at(i));
    }
}
