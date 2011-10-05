/*
 * File:   EffectInitializer.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 1:30 PM
 */

#ifndef RENDERER_EFFECTINITIALIZER_H
#define	RENDERER_EFFECTINITIALIZER_H

#include <memory>

namespace Renderer
{
    class Effect;
    class EffectRequest;

    class EffectInitializer
    {
    public:
        static void initialize(const std::shared_ptr<Effect>& effect, const EffectRequest& request);
    };
}

#endif	/* RENDERER_EFFECTINITIALIZER_H */

