/* 
 * File:   SceneNode.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 9:11 AM
 */

#ifndef GRAPHICS_SCENENODE_H
#define	GRAPHICS_SCENENODE_H

#include <boost/shared_ptr.hpp>

#include "Math/Matrix4.h"

namespace Graphics
{
    class Renderer;
    class Mesh;
    
    class SceneNode
    {
    public:
        SceneNode();
        ~SceneNode();
        
        void prepare(Renderer* renderer);
        
        void setTransform(const Math::Matrix4& transform);
        
        void addChild(const boost::shared_ptr<SceneNode>& node);
        void addMesh(const boost::shared_ptr<Mesh>& mesh);
         
    private:
        std::vector<boost::shared_ptr<SceneNode> > children;
//        Math::Matrix4 transform;
        
        std::vector<boost::shared_ptr<Mesh> > meshes;
    };
}

#endif	/* GRAPHICS_SCENENODE_H */

