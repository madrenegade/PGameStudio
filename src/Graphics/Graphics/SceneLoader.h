/*
 * File:   SceneLoader.h
 * Author: madrenegade
 *
 * Created on September 21, 2011, 9:58 AM
 */

#ifndef GRAPHICS_SCENELOADER_H
#define	GRAPHICS_SCENELOADER_H

#include <boost/shared_ptr.hpp>

#include "Math/Vector4.h"
#include "Math/Matrix4.h"

#include "Utilities/Memory/typedefs.h"
#include "Utilities/string.h"
#include "Utilities/IO/File.h"

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
        typedef std::vector<boost::shared_ptr<Camera>> Cameras;

        SceneLoader(const boost::shared_ptr<Utilities::IO::FileSystem>& fileSystem,
                    const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                    const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties,
                    Utilities::Memory::pool_id pool, Renderer* renderer);
        ~SceneLoader();

        boost::shared_ptr<SceneNode> loadFrom(const Utilities::IO::File::Handle& file);

        const Cameras& getCameras() const;

    private:
        void readHeader();
        void readTextures();
        void readMaterials();
        void readMeshes();
        void readCameras();
        boost::shared_ptr<SceneNode> readSceneGraph();

        boost::shared_ptr<SceneNode> readNode();

        template<typename T>
        const T read()
        {
            return Graphics::read<T > (&data);
        }

        boost::shared_ptr<Utilities::IO::FileSystem> fileSystem;
        boost::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        const boost::shared_ptr<Utilities::Properties::PropertyManager> properties;
        Utilities::Memory::pool_id pool;

        Renderer* renderer;

        const char* data;
        unsigned char numberSize;

        std::vector<boost::shared_ptr<Material> > materials;
        std::vector<boost::shared_ptr<Mesh> > meshes;
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

