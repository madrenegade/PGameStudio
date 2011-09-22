/* 
 * File:   SceneNode.cpp
 * Author: madrenegade
 * 
 * Created on September 17, 2011, 9:11 AM
 */

#include "Graphics/SceneNode.h"
#include "Graphics/Renderer.h"
#include "Graphics/DrawCall.h"
#include "Graphics/Mesh.h"
#include "Math/Matrix4.h"

namespace Graphics
{

    SceneNode::SceneNode()
    {
    }

    SceneNode::~SceneNode()
    {
    }

    void SceneNode::prepare(Renderer* renderer)
    {
        for (unsigned int i = 0; i < meshes.size(); ++i)
        {
            Mesh* mesh = meshes.at(i).get();
            
            if (renderer->isVertexBufferLoaded(mesh->vertexBuffer) && renderer->isIndexBufferLoaded(mesh->indexBuffer))
            {
                bool allTexturesLoaded = true;
                
                Material* mat = mesh->material.get();

                for (auto j = mat->textures.begin(); j != mat->textures.end(); ++j)
                {
                    if (!renderer->isTextureLoaded(*j))
                    {
                        allTexturesLoaded = false;
                        break;
                    }
                }

                if (allTexturesLoaded)
                {
                    DrawCall drawCall;
                    drawCall.transform = transform;
                    drawCall.vertexBuffer = mesh->vertexBuffer;
                    drawCall.indexBuffer = mesh->indexBuffer;
                    drawCall.material = mat;

                    renderer->pushDrawCall(drawCall);
                }
            }
        }

        std::for_each(children.begin(), children.end(), [&renderer](boost::shared_ptr<SceneNode> child) {
            child->prepare(renderer);
        });
    }

    void SceneNode::setTransform(const Math::Matrix4& transform)
    {
        this->transform = transform;
    }

    void SceneNode::addChild(const boost::shared_ptr<SceneNode>& node)
    {
        children.push_back(node);
    }
    
    void SceneNode::addMesh(const boost::shared_ptr<Mesh>& mesh)
    {
        meshes.push_back(mesh);
    }
}
