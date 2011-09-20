/* 
 * File:   Effect.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 9:51 AM
 */

#ifndef RENDERER_EFFECT_H
#define	RENDERER_EFFECT_H

#include <Cg/cg.h>

namespace Math
{
    class Vector2;
    class Vector3;
    class Vector4;
    class Matrix4;
}

namespace Renderer
{
    class Texture;
    
    class Effect
    {
    public:
        Effect();
        ~Effect();
        
        static void initialize();
        static void deinitialize();
        
        void load(const char* code);
        
        void set(const char* semantic, double d);
        void set(const char* semantic, const Math::Vector2& v);
        void set(const char* semantic, const Math::Vector3& v);
        void set(const char* semantic, const Math::Vector4& v);
        void set(const char* semantic, const Math::Matrix4& matrix);
        
        void set(unsigned int level, const Texture* texture);
        
        void activate();
        
        bool hasNextPass();
        void gotoNextPass();
        
        void deactivate();
        
    private:
        static CGcontext context;
        
        CGeffect effect;
        CGtechnique technique;
        CGpass currentPass;
        
        static void CgErrorHandler(CGcontext context, CGerror error, void* pData);
    };
}

#endif	/* RENDERER_EFFECT_H */

