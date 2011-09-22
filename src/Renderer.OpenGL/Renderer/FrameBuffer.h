/* 
 * File:   FrameBuffer.h
 * Author: madrenegade
 *
 * Created on September 19, 2011, 7:30 PM
 */

#ifndef RENDERER_FRAMEBUFFER_H
#define	RENDERER_FRAMEBUFFER_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include "Renderer/Texture.h"

#include "Utilities/Memory/STLAllocator.h"

namespace Renderer
{
    
    class FrameBuffer
    {
    public:
        FrameBuffer(unsigned int numColorAttachments, unsigned int width, unsigned int height);
        ~FrameBuffer();
        
        void bind();
        void unbind();
        
        const Texture* getColorAttachment(unsigned int index) const
        {
            return colorAttachments.at(index).get();
        }
        
        const Texture* getDepthAttachment() const
        {
            return depthTexture.get();
        }
        
    private:
        void createColorAttachment();
        void createDepthAttachment();
        
        unsigned int width;
        unsigned int height;
        
        unsigned int id;
        
        typedef boost::shared_ptr<Texture> TexturePtr;
        std::vector<TexturePtr, Utilities::Memory::STLAllocator<TexturePtr>> colorAttachments;
        
        boost::scoped_ptr<Texture> depthTexture;
    };
}


#endif	/* RENDERER_FRAMEBUFFER_H */

