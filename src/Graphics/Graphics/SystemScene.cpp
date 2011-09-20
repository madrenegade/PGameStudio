/* 
 * File:   SystemScene.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 2:35 PM
 */

#include "Graphics/SystemScene.h"
#include "Graphics/RenderTask.h"
#include "Graphics/Renderer.h"
#include "Graphics/VertexFormat.h"
#include "Graphics/Window.h"

#include "Graphics/MeshSceneNode.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Vertex.h"

#include "Platform/PlatformManager.h"
#include "Platform/Library.h"

#include "Utilities/IO/FileSystem.h"
#include "Utilities/IO/File.h"
#include "Utilities/string.h"

#include "Math/Vector2.h"

#include <sstream>

using namespace Utilities::Memory;

namespace Graphics
{
    const std::string SystemScene::SCENE_FILE_EXTENSION("graphics");

    SystemScene::SystemScene()
    {
    }

    SystemScene::~SystemScene()
    {
    }

    typedef boost::shared_ptr<Renderer> (*CreateFn)(const MemoryManager::Ptr&, pool_id pool);

    void SystemScene::initialize()
    {
        boost::shared_ptr<Platform::Library> lib = platformManager->libraries()->load("Renderer.OpenGL");

        CreateFn create = reinterpret_cast<CreateFn> (lib->getFunction("createRenderer"));
        
        renderer = create(memoryManager, 0);
        
        platformManager->getWindow()->getGraphicsContext()->MakeCurrent();
        renderer->initialize();
        platformManager->getWindow()->getGraphicsContext()->Release();

    }

    const char* SystemScene::getSceneFileExtension() const
    {
        return SCENE_FILE_EXTENSION.c_str();
    }

    void SystemScene::load(const Utilities::IO::File& file)
    {
        std::string s(file.getData(), file.getSize());
        std::string temp;
        
        std::istringstream stream(s);
        
        stream >> temp; // Meshes:
        unsigned int numMeshes = 0;
        stream >> numMeshes;
        
        stream >> temp; // Materials:
        unsigned int numMaterials = 0;
        stream >> numMaterials;
        
        stream >> temp; // Mesh:
        stream >> temp; // mesh id
        
        stream >> temp; // Vertices:
        unsigned int numVertices = 0;
        stream >> numVertices;
        
        stream >> temp;
        stream >> temp; // Positions: 1
        
        stream >> temp;
        stream >> temp; // Normals: 1
        
        stream >> temp;
        stream >> temp; // TexCoords: 1
        
        stream >> temp;
        stream >> temp; // Tangents: 1
        
        stream >> temp;
        stream >> temp; // Bitangents: 1
        
        boost::shared_array<char> vertexData = memoryManager->allocate<char>(numVertices * sizeof(VertexTNBT));
        VertexTNBT* vertex = reinterpret_cast<VertexTNBT*>(vertexData.get());
        
        Math::Vector3 vector;
        
        for(unsigned int v = 0; v < numVertices; ++v)
        {
            stream >> temp;
            stream >> temp; // Vertex <id>
            
            stream >> temp; // Position
            stream >> vector.X;
            stream >> vector.Y;
            stream >> vector.Z;
            
            vertex[v].position = vector;
            
            stream >> temp; // Normal
            stream >> vector.X;
            stream >> vector.Y;
            stream >> vector.Z;
            
            vertex[v].normal = vector;
            
            stream >> temp; // TexCoord
            stream >> vector.X;
            stream >> vector.Y;
            
            vertex[v].texcoords = Math::Vector2(vector.X, vector.Y);
            
            stream >> temp; // Tangent
            stream >> vector.X;
            stream >> vector.Y;
            stream >> vector.Z;
            
            vertex[v].tangent = vector;
            
            stream >> temp; // Biangent
            stream >> vector.X;
            stream >> vector.Y;
            stream >> vector.Z;
            
            vertex[v].bitangent = vector;
        }
        
        stream >> temp; // Faces:
        unsigned int numFaces = 0;
        stream >> numFaces;
        
        boost::shared_array<unsigned short> indexes = memoryManager->allocate<unsigned short>(numFaces * 3);
        
        for(unsigned int face = 0; face < numFaces; ++face)
        {
            stream >> temp;
            stream >> temp; // Face <id>
            
            stream >> temp;
            stream >> temp; // Indexes: 3
            
            stream >> indexes[face * 3];
            stream >> indexes[face * 3 + 1];
            stream >> indexes[face * 3 + 2];
        }
        
        unsigned long vbID = renderer->requestVertexBuffer(vertexData, numVertices, VertexFormat::forTNBT<VertexTNBT>());
        unsigned long ibID = renderer->requestIndexBuffer(indexes, numFaces * 3);
        
        
        Utilities::IO::File colorTexture(fileSystem->read("textures/color_map.jpg"));
        Utilities::IO::File normalTexture(fileSystem->read("textures/normal_map.jpg"));
        
        auto mat = memoryManager->construct(Material());
        mat->diffuse = Math::Vector4(1, 1, 1, 0);
        mat->textures.push_back(renderer->requestTexture(colorTexture));
        mat->textures.push_back(renderer->requestTexture(normalTexture));
        
        Utilities::IO::File effectFile(fileSystem->read("fx/default.cgfx"));
        Utilities::IO::File finalEffectFile(fileSystem->read("fx/final.cgfx"));
        renderer->requestEffect(effectFile);
        renderer->requestEffect(finalEffectFile);

        scene.reset(new MeshSceneNode(vbID, ibID, mat));
    }

    tbb::task* SystemScene::getTask(tbb::task* parent)
    {
        return new(parent->allocate_child()) RenderTask(
            renderer.get(),
            platformManager->getWindow()->getGraphicsContext(),
            scene.get());
    }
}
