/*
 * File:   OpenGLRenderer.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 9:22 PM
 */

#ifndef RENDERER_OPENGLRENDERER_H
#define	RENDERER_OPENGLRENDERER_H

#include "Graphics/Renderer.h"
#include "Graphics/DrawCall.h"

#include "Renderer/Manager.h"

#include "Renderer/VertexBufferRequest.h"
#include "Renderer/VertexBufferInitializer.h"
#include "Renderer/IndexBufferRequest.h"
#include "Renderer/IndexBufferInitializer.h"
#include "Renderer/EffectRequest.h"
#include "Renderer/EffectInitializer.h"
#include "Renderer/TextureRequest.h"
#include "Renderer/TextureInitializer.h"
#include "Renderer/DrawCallOptimizer.h"

#include "Utilities/IO/File.h"



namespace Math
{
    class Vector4;
    class Matrix4;
}

namespace Utilities
{
    namespace Properties
    {
        class PropertyManager;
    }

    namespace Memory
    {
        class MemoryManager;
    }
}

namespace Renderer
{
    class Viewport;

    class OpenGLRenderer : public Graphics::Renderer
    {
    public:
        OpenGLRenderer(Utilities::Memory::MemoryManager* const memory,
                       Utilities::Memory::pool_id pool,
                       const Utilities::Properties::PropertyManager* const properties,
                       const std::shared_ptr<Manager<VertexBuffer, VertexBufferRequest, VertexBufferInitializer> >& vbManager,
                       const std::shared_ptr<Manager<IndexBuffer, IndexBufferRequest, IndexBufferInitializer> >& ibManager,
                       const std::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer> >& effectManager,
                       const std::shared_ptr<Manager<Texture, TextureRequest, TextureInitializer> >& textureManager);
        virtual ~OpenGLRenderer();

        virtual void initialize();

        virtual void setCamera(const std::shared_ptr<Graphics::Camera>& camera);

        virtual unsigned long requestVertexBuffer(const boost::shared_array<Utilities::Memory::byte>& data,
                const unsigned int numVertices, const Graphics::VertexFormat& fmt);

        virtual unsigned long requestIndexBuffer(const boost::shared_array<unsigned int>& data, const unsigned int numIndexes);

        virtual unsigned long requestEffect(const Utilities::IO::File::Handle& file);
        virtual unsigned long requestTexture(const char* const name, Utilities::IO::File::Handle& file);
        virtual bool isTextureRequested(const char* const name);
        virtual unsigned long getTexture(const char* const name);

        virtual bool isVertexBufferLoaded(const unsigned long vbID) const;
        virtual bool isIndexBufferLoaded(const unsigned long ibID) const;
        virtual bool isEffectLoaded(const unsigned long effectID) const;
        virtual bool isTextureLoaded(const unsigned long textureID) const;

        virtual void beginScene();

        virtual void processDrawCalls();

    protected:
        virtual void processVertexBufferRequests();
        virtual void processIndexBufferRequests();
        virtual void processEffectRequests();
        virtual void processTextureRequests();

    private:
        void renderToFrameBuffer(const DrawCallOptimizer::DrawCalls& drawCallList, unsigned int firstAttachment);
        void renderToTexture(unsigned int viewIndex, unsigned int firstAttachment);
        void renderToScreen();

        void renderGeometry(const DrawCallOptimizer::DrawCalls& drawCallList, Effect* effect,
                            const Math::Matrix4& viewMatrix);

        void getViewVectors(Math::Vector4* v, const Graphics::Camera* camera);

        Utilities::Memory::MemoryManager* const memory;
        Utilities::Memory::pool_id pool;

        const Utilities::Properties::PropertyManager* const properties;

        std::shared_ptr<Manager<VertexBuffer, VertexBufferRequest, VertexBufferInitializer > > vertexBuffers;
        std::shared_ptr<Manager<IndexBuffer, IndexBufferRequest, IndexBufferInitializer > > indexBuffers;
        std::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer> > effects;
        std::shared_ptr<Manager<Texture, TextureRequest, TextureInitializer> > textures;

        DrawCallOptimizer drawCallOptimizer;

        unsigned int width;
        unsigned int height;
        double fieldOfView;
        double zNear;
        double zFar;

        std::shared_ptr<Graphics::Camera> camera;
        std::shared_ptr<Viewport> viewport;
    };
}

#endif	/* RENDERER_OPENGLRENDERER_H */

