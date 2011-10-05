/*
 * File:   SceneNode.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 9:11 AM
 */

#ifndef GRAPHICS_SCENENODE_H
#define	GRAPHICS_SCENENODE_H



#include "Utilities/Memory/STLAllocator.h"
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

        void addChild(const std::shared_ptr<SceneNode>& node);
        void addMesh(const std::shared_ptr<Mesh>& mesh);

    private:
        typedef std::shared_ptr<SceneNode> SceneNodePtr;
        std::vector<SceneNodePtr, Utilities::Memory::STLAllocator<SceneNodePtr>> children;

        Math::Matrix4 transform;

        typedef std::shared_ptr<Mesh> MeshPtr;
        std::vector<MeshPtr, Utilities::Memory::STLAllocator<MeshPtr>> meshes;
    };
}

#endif	/* GRAPHICS_SCENENODE_H */

