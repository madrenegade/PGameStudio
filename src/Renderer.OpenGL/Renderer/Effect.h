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
        
        void setTexture(const char* semantic, unsigned int id);
        
        void activate();
        
        bool hasNextPass();
        void gotoNextPass();
        
        void deactivate();
        
    private:
        CGcontext context;
        
        CGeffect effect;
        CGtechnique technique;
        CGpass currentPass;
        
        CGparameter modelViewProjection;
        CGparameter modelView;
        
        static void CgErrorHandler(CGcontext context, CGerror error, void* pData);
    };
}

#endif	/* RENDERER_EFFECT_H */

