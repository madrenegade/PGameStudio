/*
 * File:   VertexBufferInitializer.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 1:25 PM
 */

#ifndef RENDERER_VERTEXBUFFERINITIALIZER_H
#define	RENDERER_VERTEXBUFFERINITIALIZER_H

#include <memory>

namespace Renderer
{
    class VertexBuffer;
    class VertexBufferRequest;

    class VertexBufferInitializer
    {
    public:
        static void initialize(const std::shared_ptr<VertexBuffer>& vb, const VertexBufferRequest& request);
    };
}

#endif	/* RENDERER_VERTEXBUFFERINITIALIZER_H */

