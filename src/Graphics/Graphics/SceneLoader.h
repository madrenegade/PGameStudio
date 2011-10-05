/*
 * File:   SceneLoader.h
 * Author: madrenegade
 *
 * Created on September 21, 2011, 9:58 AM
 */

#ifndef GRAPHICS_SCENELOADER_H
#define	GRAPHICS_SCENELOADER_H



#include "Math/Vector4.h"
#include "Math/Matrix4.h"

#include "Utilities/Memory/typedefs.h"
#include "Utilities/string.h"
#include "Utilities/IO/File.h"
#include "Utilities/Memory/STLAllocator.h"

namespace Utilities
{
    namespace IO
    {
        class FileSystem;
    }

    namespace Memory
    {
        class MemoryManager;
    }
}

namespace Graphics
{
    class Renderer;
    class SceneNode;
    class Material;
    class Mesh;
    class Camera;

    template<typename T>
    const T read(const char** from)
    {
        const T obj = *reinterpret_cast<const T*> (*from);
        *from += sizeof (T);

        return obj;
    }

    class SceneLoader
    {
    public:
        typedef std::shared_ptr<Camera> CameraPtr;
        typedef std::vector<CameraPtr, Utilities::Memory::STLAllocator<CameraPtr>> Cameras;

        SceneLoader(Utilities::IO::FileSystem* const fileSystem,
                    Utilities::Memory::MemoryManager* const memoryManager,
                    const Utilities::Properties::PropertyManager* const properties,
                    Utilities::Memory::pool_id pool, Renderer* const renderer);
        ~SceneLoader();

        std::shared_ptr<SceneNode> loadFrom(const Utilities::IO::File::Handle& file);

        const Cameras& getCameras() const;

    private:
        void readHeader();
        void readTextures();
        void readMaterials();
        void readMeshes();
        void readCameras();

        std::shared_ptr<SceneNode> readSceneGraph();
        std::shared_ptr<SceneNode> readNode();

        template<typename T>
        const T read()
        {
            return Graphics::read<T > (&data);
        }

        Utilities::IO::FileSystem* const fileSystem;
        Utilities::Memory::MemoryManager* const memoryManager;
        const Utilities::Properties::PropertyManager* const properties;
        Utilities::Memory::pool_id pool;

        Renderer* const renderer;

        const char* data;
        unsigned char numberSize;

        typedef std::shared_ptr<Material> MaterialPtr;
        typedef std::shared_ptr<Mesh> MeshPtr;

        std::vector<MaterialPtr, Utilities::Memory::STLAllocator<MaterialPtr>> materials;
        std::vector<MeshPtr, Utilities::Memory::STLAllocator<MeshPtr>> meshes;
        Cameras cameras;
    };

    template<>
    const String read(const char** from);

    template<>
    const Math::Vector3 read(const char** from);

    template<>
    const Math::Vector4 read(const char** from);

    template<>
    const Math::Matrix4 read(const char** from);
}

#endif	/* GRAPHICS_SCENELOADER_H */

