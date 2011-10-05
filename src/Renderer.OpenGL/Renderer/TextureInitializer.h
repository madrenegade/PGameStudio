/*
 * File:   TextureInitializer.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 6:30 PM
 */

#ifndef RENDERER_TEXTUREINITIALIZER_H
#define	RENDERER_TEXTUREINITIALIZER_H

#include <memory>

namespace Renderer
{
    class Texture;
    class TextureRequest;

    class TextureInitializer
    {
    public:
        static void initialize(const std::shared_ptr<Texture>& texture, const TextureRequest& request);
    };
}

#endif	/* RENDERER_TEXTUREINITIALIZER_H */

