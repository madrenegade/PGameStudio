/* 
 * File:   IndexBufferRequest.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 1:10 PM
 */

#ifndef RENDERER_INDEXBUFFERREQUEST_H
#define	RENDERER_INDEXBUFFERREQUEST_H

#include <boost/shared_array.hpp>

namespace Renderer
{
    struct IndexBufferRequest
    {
        unsigned long id;
        boost::shared_array<unsigned int> data;
        unsigned int numIndexes;
    };
}

#endif	/* RENDERER_INDEXBUFFERREQUEST_H */

