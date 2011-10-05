/*
 * File:   EffectInitializer.cpp
 * Author: madrenegade
 *
 * Created on September 18, 2011, 1:30 PM
 */

#include "Renderer/EffectInitializer.h"
#include "Renderer/EffectRequest.h"
#include "Renderer/Effect.h"

#include "Utilities/string.h"

namespace Renderer
{
    void EffectInitializer::initialize(const std::shared_ptr<Effect>& effect, const EffectRequest& request)
    {
        String code(request.file->getData(), request.file->getSize());
        effect->load(code.c_str());
    }
}

