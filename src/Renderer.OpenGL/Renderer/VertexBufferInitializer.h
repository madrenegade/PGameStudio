/* 
 * File:   VertexBufferInitializer.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 1:25 PM
 */

#ifndef RENDERER_VERTEXBUFFERINITIALIZER_H
#define	RENDERER_VERTEXBUFFERINITIALIZER_H

#include <boost/shared_ptr.hpp>

namespace Renderer
{
    class VertexBuffer;
    class VertexBufferRequest;

    class VertexBufferInitializer
    {
    public:
        static void initialize(const boost::shared_ptr<VertexBuffer>& vb, const VertexBufferRequest& request);
    };
}

#endif	/* RENDERER_VERTEXBUFFERINITIALIZER_H */

