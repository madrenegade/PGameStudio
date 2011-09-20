#ifndef SCENENODE_H
#define SCENENODE_H

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class SceneNode
{
public:
    std::vector<boost::shared_ptr<SceneNode> > children;
    std::string name;
};

#endif // SCENENODE_H
