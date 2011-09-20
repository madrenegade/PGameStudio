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

    MeshSceneNode::MeshSceneNode(unsigned long vbID, unsigned long ibID, const boost::shared_ptr<Material>& mat)
    : vb(vbID), ib(ibID), mat(mat)
    {
    }

    MeshSceneNode::~MeshSceneNode()
    {
    }

    void MeshSceneNode::prepare(Renderer* renderer)
    {
        if (renderer->isVertexBufferLoaded(vb) && renderer->isIndexBufferLoaded(ib))
        {
            bool allTexturesLoaded = true;

            for (auto i = mat->textures.begin(); i != mat->textures.end(); ++i)
            {
                if (!renderer->isTextureLoaded(*i))
                {
                    allTexturesLoaded = false;
                    break;
                }
            }

            if (allTexturesLoaded)
            {
                DrawCall drawCall;
                drawCall.vertexBuffer = vb;
                drawCall.indexBuffer = ib;
                drawCall.material = mat.get();

                renderer->pushDrawCall(drawCall);
            }
        }

        SceneNode::prepare(renderer);
    }
}
