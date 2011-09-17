/* 
 * File:   Effect.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 9:51 AM
 */

#ifndef RENDERER_EFFECT_H
#define	RENDERER_EFFECT_H

#include <Cg/cg.h>

namespace Renderer
{

    class Effect
    {
    public:
        Effect();
        ~Effect();
        
        void load(const char* code);
        
        void activate();
        void deactivate();
        
    private:
        CGcontext context;
        
        CGeffect effect;
        CGtechnique technique;
        CGpass currentPass;
        
        CGparameter modelViewProjection;
        
        static void CgErrorHandler(CGcontext context, CGerror error, void* pData);
    };
}

#endif	/* RENDERER_EFFECT_H */

