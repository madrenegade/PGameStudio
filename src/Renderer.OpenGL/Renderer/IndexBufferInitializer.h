/* 
 * File:   IndexBufferInitializer.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 1:29 PM
 */

#ifndef RENDERER_INDEXBUFFERINITIALIZER_H
#define	RENDERER_INDEXBUFFERINITIALIZER_H

#include <boost/shared_ptr.hpp>

namespace Renderer
{
    class IndexBuffer;
    class IndexBufferRequest;
    
    class IndexBufferInitializer
    {
    public:
        static void initialize(const boost::shared_ptr<IndexBuffer>&, const IndexBufferRequest& request);
    };
}

#endif	/* RENDERER_INDEXBUFFERINITIALIZER_H */

