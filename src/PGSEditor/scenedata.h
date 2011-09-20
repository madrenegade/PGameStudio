#ifndef SCENEDATA_H
#define SCENEDATA_H

#include <boost/shared_ptr.hpp>

class SceneData
{
public:
    SceneData();

    void mergeWith(const boost::shared_ptr<SceneData>& other);
};

#endif // SCENEDATA_H
