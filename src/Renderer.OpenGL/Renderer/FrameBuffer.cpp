/* 
 * File:   FrameBuffer.cpp
 * Author: madrenegade
 * 
 * Created on September 19, 2011, 7:30 PM
 */

#include "Renderer/FrameBuffer.h"
#include <GL/glew.h>

#include <glog/logging.h>

namespace Renderer
{

    FrameBuffer::FrameBuffer(unsigned int numColorAttachments, unsigned int width, unsigned int height)
    : width(width), height(height)
    {
        VLOG(2) << "creating framebuffer with size " << width << "x" << height;
        //        GLint maxbuffers;
        //        glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxbuffers);
        //        
        //        if(numRenderTargets > maxbuffers)
        //        {
        //            LOG(FATAL) << "Max available render targets: " << maxbuffers;
        //        }
        glGenFramebuffers(1, &id);
        bind();

        for(unsigned int i = 0; i < numColorAttachments; ++i)
        {
            createColorAttachment();
        }
        
        createDepthAttachment();
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG(FATAL) << "Frame buffer status incomplete";
        }

        glDrawBuffer(GL_NONE);

        unbind();
    }

    FrameBuffer::~FrameBuffer()
    {
    }
    
    void FrameBuffer::createColorAttachment()
    {
        VLOG(2) << "Create color attachment " << colorAttachments.size();
        
        boost::shared_ptr<Texture> colorAttachmentTexture(new Texture());
        colorAttachmentTexture->bind();
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorAttachments.size(), GL_TEXTURE_2D, colorAttachmentTexture->getID(), 0);
        
        colorAttachments.push_back(colorAttachmentTexture);
    }
    
    void FrameBuffer::createDepthAttachment()
    {
        VLOG(2) << "creating depth buffer";
        
        depthTexture.reset(new Texture());
        depthTexture->bind();
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture->getID(), 0);
    }
    
    void FrameBuffer::bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }
    
    void FrameBuffer::unbind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
