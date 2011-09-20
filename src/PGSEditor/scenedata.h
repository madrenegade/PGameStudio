#ifndef SCENEDATA_H
#define SCENEDATA_H

#include <boost/shared_ptr.hpp>
#include <vector>

class Mesh;

class SceneNode;

class SceneData
{
public:
    SceneData();

    void mergeWith(const boost::shared_ptr<SceneData>& other);

    std::vector<boost::shared_ptr<Mesh> > meshes;

    boost::shared_ptr<SceneNode> rootNode;
};

#endif // SCENEDATA_H
