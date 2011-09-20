#ifndef SCENENODE_H
#define SCENENODE_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace Math
{
    class Matrix4;
}

class Mesh;

class SceneNode
{
public:
    std::vector<Mesh*> meshes;
    std::vector<boost::shared_ptr<SceneNode> > children;

    std::string name;

    boost::shared_ptr<Math::Matrix4> transform;
};

#endif // SCENENODE_H
