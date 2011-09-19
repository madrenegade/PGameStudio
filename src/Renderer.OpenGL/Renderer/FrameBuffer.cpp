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

    FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
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

        VLOG(2) << "Create color texture";
        glGenTextures(1, &colorTexture);
        glBindTexture(GL_TEXTURE_2D, colorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

        VLOG(2) << "create aux0 texture";
        glGenTextures(1, &aux0Texture);
        glBindTexture(GL_TEXTURE_2D, aux0Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, aux0Texture, 0);

        VLOG(2) << "create aux1 texture";
        glGenTextures(1, &aux1Texture);
        glBindTexture(GL_TEXTURE_2D, aux1Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, aux1Texture, 0);

        VLOG(2) << "creating depth buffer";
        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

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
    
    void FrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }
    
    void FrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
