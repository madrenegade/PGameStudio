/*
 * File:   EffectRequest.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 1:42 PM
 */

#ifndef RENDERER_EFFECTREQUEST_H
#define	RENDERER_EFFECTREQUEST_H

#include "Utilities/IO/File.h"
#include "Utilities/string.h"

namespace Renderer
{
    struct EffectRequest
    {
        unsigned long id;

        String name;
        Utilities::IO::File::Handle file;
    };
}

#endif	/* RENDERER_EFFECTREQUEST_H */

