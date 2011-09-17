/* 
 * File:   OpenGLRenderer.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 9:22 PM
 */

#include "Renderer/OpenGLRenderer.h"
#include "Renderer/VertexBufferManager.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/EffectManager.h"
#include "Renderer/Effect.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <glog/logging.h>

namespace Renderer
{

    OpenGLRenderer::OpenGLRenderer(const boost::shared_ptr<VertexBufferManager>& vbManager,
                                   const boost::shared_ptr<EffectManager>& effectManager)
    : vbID(), effectID(), vertexBuffers(vbManager), effects(effectManager)
    {
    }

    OpenGLRenderer::~OpenGLRenderer()
    {
    }
    
    void OpenGLRenderer::initialize()
    {
        glewInit();
        glViewport(0, 0, 800, 600);
        
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_FRAMEBUFFER);
        
        VLOG(2) << "creating framebuffer";
        
        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        
        GLint maxbuffers;
        glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxbuffers);
        
        VLOG(2) << "Max render targets: " << maxbuffers;
        
        VLOG(2) << "creating depth buffer";
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 800, 600);
        
        VLOG(2) << "attaching depth buffer to framebuffer";
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        
        VLOG(2) << "Creating color texture";
        
        glGenTextures(1, &colorTexture);
        glBindTexture(GL_TEXTURE_2D, colorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
        
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG(FATAL) << "Frame buffer status incomplete";
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//        
//        GLenum buffers = { GL_COLOR_ATTACHMENT0 };
//        glDrawBuffers(1, &buffers);
    }

    unsigned long OpenGLRenderer::requestVertexBuffer(const boost::shared_array<Utilities::Memory::byte>& data,
                                                      unsigned int numVertices, const Graphics::VertexFormat& fmt)
    {
        unsigned long id = vbID.fetch_and_add(1);

        VertexBufferRequest request;
        request.id = id;
        request.data = data;
        request.numVertices = numVertices;
        request.format = fmt;

        vbRequests.push(request);

        return id;
    }
    
    unsigned long OpenGLRenderer::requestEffect(const Utilities::IO::File& file)
    {
        unsigned long id = effectID.fetch_and_add(1);
        
        effectRequests.push(std::make_pair(id, file));
        
        return id;
    }

    bool OpenGLRenderer::isVertexBufferLoaded(unsigned long vbID) const
    {
        return vertexBuffers->isLoaded(vbID);
    }
    
    bool OpenGLRenderer::isEffectLoaded(unsigned long effectID) const
    {
        return effects->isLoaded(effectID);
    }

    void OpenGLRenderer::beginScene()
    {
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::processDrawCalls()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Graphics::DrawCall drawCall;

        VertexBuffer* vertexBuffer;
        Effect* effect;

        while (!drawCalls.empty())
        {
            if (drawCalls.try_pop(drawCall))
            {
                vertexBuffer = vertexBuffers->get(drawCall.vertexBuffer);
                effect = effects->get(drawCall.material->effect);

                effect->activate();
                vertexBuffer->render();
                effect->deactivate();
            }
        }
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        // render quad with texture on it
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, colorTexture);
        glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex2d(0, 0);
        
        glTexCoord2d(1, 0); 
        glVertex2d(1, 0);
        
        glTexCoord2d(1, 1);
        glVertex2d(1, 1);
        
        glTexCoord2d(0, 1);
        glVertex2d(0, 1);
        
        glEnd();
    }

    void OpenGLRenderer::processVertexBufferRequests()
    {
        VertexBufferRequest request;

        while (!vbRequests.empty())
        {
            if (vbRequests.try_pop(request))
            {
                VLOG(2) << "Handling vertex buffer request with id " << request.id;

                vertexBuffers->createFrom(request);
            }
        }
    }
    
    void OpenGLRenderer::processEffectRequests()
    {
        std::pair<unsigned long, Utilities::IO::File> request;

        while (!effectRequests.empty())
        {
            if (effectRequests.try_pop(request))
            {
                VLOG(2) << "Handling effect request with id " << request.first;

                effects->createFrom(request);
            }
        }
    }
}
