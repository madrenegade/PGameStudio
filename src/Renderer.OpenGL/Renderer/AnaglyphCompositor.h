/*
 * File:   AnaglyphCompositor.h
 * Author: madrenegade
 *
 * Created on September 26, 2011, 7:55 PM
 */

#ifndef RENDERER_ANAGLYPHCOMPOSITOR_H
#define	RENDERER_ANAGLYPHCOMPOSITOR_H

#include <boost/shared_ptr.hpp>
#include "Renderer/MultiViewCompositor.h"
#include "Renderer/Manager.h"

namespace Renderer
{
    class Effect;
    class EffectRequest;
    class EffectInitializer;
    class Viewport;

    class AnaglyphCompositor : public MultiViewCompositor
    {
    public:
        AnaglyphCompositor(const Viewport* vp, const boost::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer>>& effects,
                           const unsigned int fx);
        virtual ~AnaglyphCompositor();

        virtual void startCompose() const;
        virtual void endCompose() const;

    private:
        const Viewport* const viewport;

        boost::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer>> effects;

        const unsigned int composeEffect;
    };
}

#endif	/* RENDERER_ANAGLYPHCOMPOSITOR_H */

