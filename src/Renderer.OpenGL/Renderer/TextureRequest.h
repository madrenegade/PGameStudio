/*
 * File:   TextureRequest.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 6:31 PM
 */

#ifndef RENDERER_TEXTUREREQUEST_H
#define	RENDERER_TEXTUREREQUEST_H

#include "Utilities/IO/File.h"
#include "Utilities/string.h"

namespace Renderer
{
    struct TextureRequest
    {
        String name;
        unsigned long id;
        Utilities::IO::File::Handle file;
    };
}

#endif	/* RENDERER_TEXTUREREQUEST_H */

