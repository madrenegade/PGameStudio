#ifndef RENDERER_DEFAULTCOMPOSITOR_H
#define RENDERER_DEFAULTCOMPOSITOR_H

#include <boost/shared_ptr.hpp>
#include "Renderer/MultiViewCompositor.h"
#include "Renderer/Manager.h"

namespace Renderer
{
    class Effect;
    class EffectRequest;
    class EffectInitializer;
    class Viewport;

    class DefaultCompositor : public Renderer::MultiViewCompositor
    {
    public:
        DefaultCompositor(const Viewport* const viewport, const boost::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer>>& effects,
                          const unsigned int fx);
        virtual ~DefaultCompositor();

        virtual void startCompose() const;
        virtual void endCompose() const;

    private:
        const Viewport* const viewport;
        const boost::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer>> effects;
        const unsigned int composeEffect;
    };

} // namespace Renderer

#endif // RENDERER_DEFAULTCOMPOSITOR_H
