/* 
 * File:   MeshSceneNode.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 9:14 AM
 */

#ifndef GRAPHICS_MESHSCENENODE_H
#define	GRAPHICS_MESHSCENENODE_H

#include "Graphics/SceneNode.h"
#include "Graphics/Material.h"

#include <boost/shared_ptr.hpp>

namespace Graphics
{
    
    class MeshSceneNode : public SceneNode
    {
    public:
        MeshSceneNode(unsigned long vb, unsigned long ib, const boost::shared_ptr<Material>& mat);
        virtual ~MeshSceneNode();
        
        virtual void prepare(Renderer* renderer);
        
    private:
        unsigned long vb;
        unsigned long ib;
        
        boost::shared_ptr<Material> mat;
    };
}

#endif	/* GRAPHICS_MESHSCENENODE_H */

