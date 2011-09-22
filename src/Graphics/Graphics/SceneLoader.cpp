/* 
 * File:   SceneLoader.cpp
 * Author: madrenegade
 * 
 * Created on September 21, 2011, 9:58 AM
 */

#include "Graphics/SceneLoader.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"
#include "Graphics/Renderer.h"
#include "Graphics/VertexFormat.h"
#include "Graphics/Vertex.h"
#include "Graphics/SceneNode.h"

#include "Utilities/IO/File.h"
#include "Utilities/IO/FileSystem.h"
#include "Utilities/Memory/MemoryManager.h"
#include "Math/Matrix4.h"

#include <stdexcept>
#include <glog/logging.h>

namespace Graphics
{

    template<>
    const String read(const char** from)
    {
        const unsigned int length = read<unsigned int>(from);

        String s(*from, length);
        *from += length;

        return s;
    }
    
//    template<>
//    const std::string read(const char** from)
//    {
//        const unsigned int length = read<unsigned int>(from);
//
//        std::string s(*from, length);
//        *from += length;
//
//        return s;
//    }

    template<>
    const Math::Vector4 read(const char** from)
    {
        double r = read<double>(from);
        double g = read<double>(from);
        double b = read<double>(from);
        double a = read<double>(from);
        
        return Math::Vector4(r, g, b, a);
    }
    
    template<>
    const Math::Matrix4 read(const char** from)
    {
        double d[16];
        for(unsigned int i = 0; i < 16; ++i)
        {
            d[i] = read<double>(from);
        }
        
        return Math::Matrix4(d);
    }

    SceneLoader::SceneLoader(const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                             const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                             Utilities::Memory::pool_id pool, Renderer* renderer)
    : fileSystem(fileSystem), memoryManager(memoryManager), pool(pool), renderer(renderer)
    {
    }

    SceneLoader::~SceneLoader()
    {
    }

    boost::shared_ptr<SceneNode> SceneLoader::loadFrom(const Utilities::IO::File& file)
    {
        data = file.getData();

        readHeader();
        readTextures();
        readMaterials();
        readMeshes();
        readCameras();

        return readSceneGraph();
    }

    void SceneLoader::readHeader()
    {
        VLOG(2) << "Reading header";

        numberSize = read<unsigned char>();

        if (numberSize != sizeof (double))
        {
            throw std::runtime_error("Only 64 bit numbers are supported at the moment");
        }
    }

    void SceneLoader::readTextures()
    {
    }

    void SceneLoader::readMaterials()
    {
        VLOG(2) << "Reading materials";

        const unsigned int numMaterials = read<unsigned int>();
        materials.resize(numMaterials);

        VLOG(2) << "numMaterials: " << numMaterials;

        for (unsigned int i = 0; i < numMaterials; ++i)
        {
            String name(read<String > ());
            VLOG(2) << "Material: '" << name << "'";

            boost::shared_ptr<Material> material = memoryManager->construct(Material(), pool);
            material->diffuse = read<Math::Vector4 > ();
            VLOG(2) << "Diffuse: " << material->diffuse.X << ", " << material->diffuse.Y << ", " << material->diffuse.Z << ", " << material->diffuse.W;
            material->specular = read<Math::Vector4 > ();
            VLOG(2) << "Specular: " << material->specular.X << ", " << material->specular.Y << ", " << material->specular.Z << ", " << material->specular.W;

            const unsigned int numTextures = read<unsigned int>();
            VLOG(2) << "Textures: " << numTextures;

            for (unsigned int j = 0; j < numTextures; ++j)
            {
                String textureName("textures/" + read<String > ());
                VLOG(2) << "texture: " << textureName;

                Utilities::IO::File texture(fileSystem->read(textureName.c_str()));
                material->textures.push_back(renderer->requestTexture(texture));
            }

            materials[i] = material;
        }
    }

    void SceneLoader::readMeshes()
    {
        VLOG(2) << "Reading meshes";

        const unsigned int numMeshes = read<unsigned int>();
        VLOG(2) << "numMeshes: " << numMeshes;

        for (unsigned int i = 0; i < numMeshes; ++i)
        {
            boost::shared_ptr<Mesh> mesh = memoryManager->construct(Mesh(), pool);

            const unsigned int materialID = read<unsigned int>();
            VLOG(2) << "material: " << materialID;
            mesh->material = materials[materialID];

            const bool hasPositions = read<bool>();
            const bool hasNormals = read<bool>();
            const bool hasTangents = read<bool>();
            const bool hasBitangents = read<bool>();
            const bool hasTexCoords = read<bool>();

            const unsigned int numUVChannels = read<unsigned char>();
            VLOG(2) << "NumUVChannels: " << numUVChannels;

            const unsigned int numVertices = read<unsigned int>();
            VLOG(2) << "NumVertices: " << numVertices;

            unsigned int vertexSize = 0;

            if (hasPositions) vertexSize += 3 * numberSize;
            if (hasNormals) vertexSize += 3 * numberSize;
            if (hasTangents) vertexSize += 3 * numberSize;
            if (hasBitangents) vertexSize += 3 * numberSize;
            if (hasTexCoords) vertexSize += 2 * numberSize * numUVChannels;

            if(vertexSize != sizeof(VertexTNBT))
            {
                VLOG(2) << "Positions: " << hasPositions;
                VLOG(2) << "Normals: " << hasNormals;
                VLOG(2) << "Tangents: " << hasTangents;
                VLOG(2) << "Bitangents: " << hasBitangents;
                VLOG(2) << "TexCoords: " << hasTexCoords;
                LOG(FATAL) << "Scene file contains vertex structure of size " << vertexSize << " instead of " << sizeof(VertexTNBT);
            }
            
            const unsigned int bytes = numVertices * vertexSize;
            

            boost::shared_array<char> vertexData = memoryManager->allocate<char>(bytes, pool);
            Utilities::copy(data, vertexData.get(), bytes);
            data += bytes;

            const unsigned int numFaces = read<unsigned int>();
            VLOG(2) << "numFaces: " << numFaces;

            boost::shared_array<unsigned int> indexes = memoryManager->allocate<unsigned int>(numFaces * 3, pool);

            for (unsigned int j = 0; j < numFaces; ++j)
            {
                const unsigned int numIndexes = read<unsigned char>();

                if (numIndexes != 3)
                {
                    throw std::runtime_error("Only triangles are supported at the moment");
                }

                for (unsigned int k = 0; k < numIndexes; ++k)
                {
                    indexes[j * 3 + k] = read<unsigned int>();
                }
            }

            mesh->vertexBuffer = renderer->requestVertexBuffer(vertexData, numVertices, VertexFormat::forTNBT<VertexTNBT > ());
            mesh->indexBuffer = renderer->requestIndexBuffer(indexes, numFaces * 3);

            meshes.push_back(mesh);
        }
    }

    void SceneLoader::readCameras()
    {
        VLOG(2) << "Reading cameras";
    }

    boost::shared_ptr<SceneNode> SceneLoader::readSceneGraph()
    {
        VLOG(2) << "Reading scene graph";
        
        return readNode();
    }
    
    boost::shared_ptr<SceneNode> SceneLoader::readNode()
    {
        // construction fails in 64bit debug mode because
        // backtrace from glibc crashes for recursive functions
#if defined GCC && defined X64 && defined DEBUG
        boost::shared_ptr<SceneNode> node(new SceneNode());
#else
        boost::shared_ptr<SceneNode> node = memoryManager->construct(SceneNode(), pool);
#endif
        
        String name(read<String>());
        VLOG(2) << "Reading scene node " << name;
        
        node->setTransform(read<Math::Matrix4>());
        
        const unsigned int numMeshes = read<unsigned int>();
        
        for(unsigned int i = 0; i < numMeshes; ++i)
        {
            const unsigned int meshIndex = read<unsigned int>();
            node->addMesh(meshes.at(meshIndex));
        }
        
        const unsigned int numChildren = read<unsigned int>();
        
        for(unsigned int i = 0; i < numChildren; ++i)
        {
            node->addChild(readNode());
        }
        
        return node;
    }
}