/* 
 * File:   FrameBuffer.h
 * Author: madrenegade
 *
 * Created on September 19, 2011, 7:30 PM
 */

#ifndef RENDERER_FRAMEBUFFER_H
#define	RENDERER_FRAMEBUFFER_H

namespace Renderer
{

    class FrameBuffer
    {
    public:
        FrameBuffer(unsigned int width, unsigned int height);
        ~FrameBuffer();
        
        void bind();
        void unbind();
        
        unsigned int getColorTexture() const
        {
            return colorTexture;
        }
        
        unsigned int getAux0Texture() const
        {
            return aux0Texture;
        }
        
        unsigned int getAux1Texture() const
        {
            return aux1Texture;
        }
        
        unsigned int getDepthTexture() const
        {
            return depthTexture;
        }
        
    private:
        unsigned int id;
        
        unsigned int colorTexture;
        unsigned int aux0Texture;
        unsigned int aux1Texture;
        unsigned int depthTexture;
    };
}


#endif	/* RENDERER_FRAMEBUFFER_H */

