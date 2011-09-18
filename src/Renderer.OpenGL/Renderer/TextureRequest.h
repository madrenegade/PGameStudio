/* 
 * File:   TextureRequest.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 6:31 PM
 */

#ifndef RENDERER_TEXTUREREQUEST_H
#define	RENDERER_TEXTUREREQUEST_H

#include "Utilities/IO/File.h"

namespace Renderer
{
    struct TextureRequest
    {
        unsigned long id;
        Utilities::IO::File file;
    };
}

#endif	/* RENDERER_TEXTUREREQUEST_H */

