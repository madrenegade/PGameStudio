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

#include "Utilities/IO/File.h"

#include <boost/shared_ptr.hpp>

namespace Renderer
{
    class FrameBuffer;
    
    class OpenGLRenderer : public Graphics::Renderer
    {
    public:
        OpenGLRenderer(const boost::shared_ptr<Manager<VertexBuffer, VertexBufferRequest, VertexBufferInitializer> >& vbManager,
                       const boost::shared_ptr<Manager<IndexBuffer, IndexBufferRequest, IndexBufferInitializer> >& ibManager,
                       const boost::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer> >& effectManager,
                       const boost::shared_ptr<Manager<Texture, TextureRequest, TextureInitializer> >& textureManager);
        virtual ~OpenGLRenderer();

        virtual void initialize();

        virtual unsigned long requestVertexBuffer(const boost::shared_array<Utilities::Memory::byte>& data,
                                                  unsigned int numVertices, const Graphics::VertexFormat& fmt);

        virtual unsigned long requestIndexBuffer(const boost::shared_array<unsigned short>& data, unsigned int numIndexes);

        virtual unsigned long requestEffect(const Utilities::IO::File& file);
        virtual unsigned long requestTexture(const Utilities::IO::File& file);

        virtual bool isVertexBufferLoaded(unsigned long vbID) const;
        virtual bool isIndexBufferLoaded(unsigned long ibID) const;
        virtual bool isEffectLoaded(unsigned long effectID) const;
        virtual bool isTextureLoaded(unsigned long textureID) const;

        virtual void beginScene();

        virtual void processDrawCalls();

    protected:
        virtual void processVertexBufferRequests();
        virtual void processIndexBufferRequests();
        virtual void processEffectRequests();
        virtual void processTextureRequests();

    private:
        boost::shared_ptr<Manager<VertexBuffer, VertexBufferRequest, VertexBufferInitializer > > vertexBuffers;
        boost::shared_ptr<Manager<IndexBuffer, IndexBufferRequest, IndexBufferInitializer > > indexBuffers;
        boost::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer> > effects;
        boost::shared_ptr<Manager<Texture, TextureRequest, TextureInitializer> > textures;

        boost::shared_ptr<FrameBuffer> frameBuffer;
//        unsigned int frameBuffer;
//
//        unsigned int colorTexture;
//        unsigned int aux0Texture;
//        unsigned int aux1Texture;
//        unsigned int depthTexture;
    };
}

#endif	/* RENDERER_OPENGLRENDERER_H */

