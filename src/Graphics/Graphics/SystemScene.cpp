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
    
    void readNode(const char** data)
    {
        const unsigned int nodeNameLength = *reinterpret_cast<const unsigned int*> (*data);
        *data += sizeof (nodeNameLength);

        std::string name(*data, nodeNameLength);
        LOG(INFO) << "Node: '" << name << "'";
        *data += nodeNameLength;

        *data += 16 * sizeof(double);

        const unsigned int numMeshes = *reinterpret_cast<const unsigned int*> (*data);
        LOG(INFO) << "numMeshes: " << numMeshes;
        *data += sizeof (numMeshes); 

        *data += numMeshes * sizeof(unsigned int);

        const unsigned int numChildren = *reinterpret_cast<const unsigned int*> (*data);
        LOG(INFO) << "numChildren: " << numChildren;
        *data += sizeof(numChildren);
        
        for(unsigned int i = 0; i < numChildren; ++i)
        {
            readNode(data);
        }
    }

    void SystemScene::load(const Utilities::IO::File& file)
    {
        const char* data = file.getData();

        unsigned char sizeofDouble = data[0];
        LOG(INFO) << "NumberSize: " << static_cast<unsigned short> (sizeofDouble);
        ++data;

        // textures

        // materials
        const unsigned int numMaterials = *reinterpret_cast<const unsigned int*> (data);
        LOG(INFO) << "numMaterials: " << numMaterials;
        data += sizeof (numMaterials);

        for (unsigned int i = 0; i < numMaterials; ++i)
        {
            const unsigned int nameLength = *reinterpret_cast<const unsigned int*> (data);
            data += sizeof (nameLength);

            std::string name(data, nameLength);
            LOG(INFO) << "Material: '" << name << "'";
            data += nameLength;

            Math::Vector4 diffuse;
            diffuse.X = *reinterpret_cast<const double*> (data);
            data += sizeofDouble;
            diffuse.Y = *reinterpret_cast<const double*> (data);
            data += sizeofDouble;
            diffuse.Z = *reinterpret_cast<const double*> (data);
            data += sizeofDouble;
            diffuse.W = *reinterpret_cast<const double*> (data);
            data += sizeofDouble;

            Math::Vector4 specular;
            specular.X = *reinterpret_cast<const double*> (data);
            data += sizeofDouble;
            specular.Y = *reinterpret_cast<const double*> (data);
            data += sizeofDouble;
            specular.Z = *reinterpret_cast<const double*> (data);
            data += sizeofDouble;
            specular.W = *reinterpret_cast<const double*> (data);
            data += sizeofDouble;
        }

        // meshes
        const unsigned int numMeshes = *reinterpret_cast<const unsigned int*> (data);
        LOG(INFO) << "numMeshes: " << numMeshes;
        data += sizeof (numMeshes);

        for (unsigned int i = 0; i < numMeshes; ++i)
        {
            const bool hasPositions = *reinterpret_cast<const bool*> (data);
            data += sizeof (hasPositions);

            const bool hasNormals = *reinterpret_cast<const bool*> (data);
            data += sizeof (hasNormals);

            const bool hasTangents = *reinterpret_cast<const bool*> (data);
            data += sizeof (hasTangents);

            const bool hasBitangents = *reinterpret_cast<const bool*> (data);
            data += sizeof (hasBitangents);

            const bool hasTexCoords = *reinterpret_cast<const bool*> (data);
            data += sizeof (hasTexCoords);

            const unsigned int numUVChannels = *data;
            LOG(INFO) << "NumUVChannels: " << numUVChannels;
            ++data;

            const unsigned int numVertices = *reinterpret_cast<const unsigned int*> (data);
            LOG(INFO) << "NumVertices: " << numVertices;
            data += sizeof (numVertices);

            unsigned int vertexSize = 0;

            if (hasPositions) vertexSize += 3 * sizeofDouble;
            if (hasNormals) vertexSize += 3 * sizeofDouble;
            if (hasTangents) vertexSize += 3 * sizeofDouble;
            if (hasBitangents) vertexSize += 3 * sizeofDouble;
            if (hasTexCoords) vertexSize += 2 * sizeofDouble * numUVChannels;

            const unsigned int bytes = numVertices * vertexSize;
            boost::shared_array<char> vertexData = memoryManager->allocate<char>(bytes);
            Utilities::copy(data, vertexData.get(), bytes);
            data += bytes;

            const unsigned int numFaces = *reinterpret_cast<const unsigned int*> (data);
            LOG(INFO) << "numFaces: " << numFaces;
            data += sizeof (numFaces);

            boost::shared_array<unsigned short> indexes = memoryManager->allocate<unsigned short>(numFaces * 3);

            for (unsigned int j = 0; j < numFaces; ++j)
            {
                const unsigned int numIndexes = *data;
                ++data;

                if (numIndexes != 3)
                {
                    throw std::runtime_error("Only triangles are supported at the moment");
                }

                for (unsigned int k = 0; k < numIndexes; ++k)
                {
                    indexes[j * 3 + k] = *reinterpret_cast<const unsigned short*> (data);
                    data += sizeof (unsigned short);
                }
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

        // cameras

        // scene graph
        readNode(&data);
    }

    tbb::task* SystemScene::getTask(tbb::task* parent)
    {
        return new(parent->allocate_child()) RenderTask(
            renderer.get(),
            platformManager->getWindow()->getGraphicsContext(),
            scene.get());
    }
}
