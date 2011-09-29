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

#include "Renderer/Texture.h"

#include "Utilities/Memory/STLAllocator.h"

namespace Renderer
{

    class FrameBuffer
    {
    public:
        FrameBuffer(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager,
                    Utilities::Memory::pool_id pool,
                    const unsigned int numColorAttachments, const unsigned int width, const unsigned int height);
        ~FrameBuffer();

        void bind() const;
        void unbind() const;

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
        
        const boost::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        const Utilities::Memory::pool_id pool;

        const unsigned int width;
        const unsigned int height;

        unsigned int id;

        typedef boost::shared_ptr<Texture> TexturePtr;
        std::vector<TexturePtr, Utilities::Memory::STLAllocator<TexturePtr >> colorAttachments;

        boost::shared_ptr<Texture> depthTexture;
    };
}


#endif	/* RENDERER_FRAMEBUFFER_H */

