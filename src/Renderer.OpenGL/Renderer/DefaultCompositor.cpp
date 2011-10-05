#include "Renderer/DefaultCompositor.h"
#include "Renderer/Viewport.h"
#include "Renderer/FrameBuffer.h"
#include "Renderer/Texture.h"
#include "Renderer/Effect.h"

namespace Renderer
{

    DefaultCompositor::DefaultCompositor(const Viewport* const viewport, const std::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer>>& effects,
                                         const unsigned int fx)
        : viewport(viewport), effects(effects), composeEffect(fx)
    {
        //ctor
    }

    DefaultCompositor::~DefaultCompositor()
    {
        //dtor
    }

    void DefaultCompositor::startCompose() const
    {
        const Texture* texture = viewport->getFrameBuffer()->getColorAttachment(3);
        texture->bind(0);

        Effect* effect = effects->get(composeEffect);
        effect->set(0, texture);
        effect->activate();
    }

    void DefaultCompositor::endCompose() const
    {
        Effect* effect = effects->get(composeEffect);
        effect->deactivate();

        const Texture* texture = viewport->getFrameBuffer()->getColorAttachment(3);
        texture->unbind(0);
    }

} // namespace Renderer
