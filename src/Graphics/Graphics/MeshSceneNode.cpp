/* 
 * File:   MeshSceneNode.cpp
 * Author: madrenegade
 * 
 * Created on September 17, 2011, 9:14 AM
 */

#include "Graphics/MeshSceneNode.h"
#include "Graphics/Renderer.h"
#include "Graphics/DrawCall.h"

namespace Graphics
{

    MeshSceneNode::MeshSceneNode(unsigned long vbID, unsigned long ibID, unsigned long effect)
    : vb(vbID), ib(ibID)
    {
        mat.effect = effect;
    }

    MeshSceneNode::~MeshSceneNode()
    {
    }
    
    void MeshSceneNode::prepare(Renderer* renderer)
    {
        if(renderer->isVertexBufferLoaded(vb) && renderer->isIndexBufferLoaded(ib) && renderer->isEffectLoaded(mat.effect))
        {
            DrawCall drawCall;
            drawCall.vertexBuffer = vb;
            drawCall.indexBuffer = ib;
            drawCall.material = &mat;
            
            renderer->pushDrawCall(drawCall);
        }
        
        SceneNode::prepare(renderer);
    }
}
