/*
 * File:   Renderer.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 9:09 PM
 */

#ifndef GRAPHICS_RENDERER_H
#define	GRAPHICS_RENDERER_H

#include "Utilities/Memory/typedefs.h"
#include "Utilities/IO/File.h"

#include "Core/Events/EventManager.h"

#include <boost/shared_array.hpp>
#include <tbb/concurrent_queue.h>

namespace Graphics
{
    class VertexFormat;
    class DrawCall;
    class Camera;

    class Renderer
    {
    public:
        virtual ~Renderer();

        virtual void initialize() = 0;
        virtual void setCamera(const boost::shared_ptr<Camera>& camera) = 0;

        virtual unsigned long requestVertexBuffer(const boost::shared_array<Utilities::Memory::byte>& data, const unsigned int numVertices, const VertexFormat& fmt) = 0;

        //        virtual unsigned long requestIndexBuffer(const boost::shared_array<unsigned char>& data, unsigned int numIndexes) = 0;
        virtual unsigned long requestIndexBuffer(const boost::shared_array<unsigned int>& data, const unsigned int numIndexes) = 0;
        //        virtual unsigned long requestIndexBuffer(const boost::shared_array<unsigned int>& data, unsigned int numIndexes) = 0;

        virtual unsigned long requestEffect(const Utilities::IO::File::Handle& file) = 0;
        virtual unsigned long requestTexture(const Utilities::IO::File::Handle& file) = 0;

        virtual bool isVertexBufferLoaded(const unsigned long vbID) const = 0;
        virtual bool isIndexBufferLoaded(const unsigned long ibID) const = 0;
        virtual bool isEffectLoaded(const unsigned long effectID) const = 0;
        virtual bool isTextureLoaded(const unsigned long textureID) const = 0;

        virtual void beginScene() = 0;

        void processRequests();

        void pushDrawCall(const DrawCall& drawCall);

        virtual void processDrawCalls() = 0;

    protected:
        Renderer();

        virtual void processVertexBufferRequests() = 0;
        virtual void processIndexBufferRequests() = 0;
        virtual void processEffectRequests() = 0;
        virtual void processTextureRequests() = 0;

        tbb::concurrent_queue<DrawCall> drawCalls;
    };
}

#endif	/* GRAPHICS_RENDERER_H */

