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

    MeshSceneNode::MeshSceneNode(unsigned long vbID, unsigned long effect)
    : vb(vbID)
    {
        mat.effect = effect;
    }

    MeshSceneNode::~MeshSceneNode()
    {
    }
    
    void MeshSceneNode::prepare(Renderer* renderer)
    {
        if(renderer->isVertexBufferLoaded(vb) && renderer->isEffectLoaded(mat.effect))
        {
            DrawCall drawCall;
            drawCall.vertexBuffer = vb;
            drawCall.material = &mat;
            
            renderer->pushDrawCall(drawCall);
        }
        
        SceneNode::prepare(renderer);
    }
}
