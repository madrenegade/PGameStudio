/* 
 * File:   AnaglyphCompositor.cpp
 * Author: madrenegade
 * 
 * Created on September 26, 2011, 7:55 PM
 */

#include "Renderer/AnaglyphCompositor.h"
#include "Effect.h"
#include "EffectRequest.h"
#include "Viewport.h"
#include "FrameBuffer.h"

namespace Renderer
{

    AnaglyphCompositor::AnaglyphCompositor(const Viewport* vp, const boost::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer>>& effects,
                                           unsigned int fx)
    : viewport(vp), effects(effects), composeEffect(fx)
    {
        
    }

    AnaglyphCompositor::~AnaglyphCompositor()
    {
    }
    
    void AnaglyphCompositor::startCompose() const
    {
        const Texture* leftTexture = viewport->getFrameBuffer(0)->getColorAttachment(3);
        leftTexture->bind(0);
        
        const Texture* rightTexture = viewport->getFrameBuffer(1)->getColorAttachment(3);
        rightTexture->bind(1);
        
        Effect* effect = effects->get(composeEffect);
        
        effect->set(0, leftTexture);
        effect->set(1, rightTexture);
        
        effect->activate();
    }
    
    void AnaglyphCompositor::endCompose() const
    {
        Effect* effect = effects->get(composeEffect);
        effect->deactivate();
    }
}
