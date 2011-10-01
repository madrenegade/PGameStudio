#ifndef SCENEDATA_H
#define SCENEDATA_H

#include <boost/shared_ptr.hpp>
#include <vector>

class Material;
class Mesh;
class Camera;

class SceneNode;

struct SceneData
{
    void mergeWith(const boost::shared_ptr<SceneData>& other);

    std::vector<boost::shared_ptr<Material> > materials;
    std::vector<boost::shared_ptr<Mesh> > meshes;
    std::vector<boost::shared_ptr<Camera> > cameras;

    boost::shared_ptr<SceneNode> rootNode;
};

#endif // SCENEDATA_H
