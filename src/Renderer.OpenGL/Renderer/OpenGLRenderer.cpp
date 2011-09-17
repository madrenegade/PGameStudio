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
#include <GL/glu.h>
#include <glog/logging.h>
#include <list>

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
        glEnable(GL_DEPTH_TEST);

        check();

        VLOG(2) << "creating framebuffer";

        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

        GLint maxbuffers;
        glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxbuffers);

        VLOG(2) << "Max render targets: " << maxbuffers;
        check();

        VLOG(2) << "Create color texture";
        glGenTextures(1, &colorTexture);
        glBindTexture(GL_TEXTURE_2D, colorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        check();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

        VLOG(2) << "create aux0 texture";
        glGenTextures(1, &aux0Texture);
        glBindTexture(GL_TEXTURE_2D, aux0Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        check();
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, aux0Texture, 0);

        VLOG(2) << "create aux1 texture";
        glGenTextures(1, &aux1Texture);
        glBindTexture(GL_TEXTURE_2D, aux1Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        check();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, aux1Texture, 0);

        VLOG(2) << "creating depth buffer";
        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri (GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 800, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        check();
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
        
        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, 800, 600);
        check();

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        check();


        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG(FATAL) << "Frame buffer status incomplete";
        }
        
        glDrawBuffer(GL_NONE);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
       
        check();
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
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::processDrawCalls()
    {
        std::list<Graphics::DrawCall> drawCallList;

        Graphics::DrawCall drawCall;
        while (!drawCalls.empty())
        {
            if (drawCalls.try_pop(drawCall))
            {
                drawCallList.push_back(drawCall);
            }
        }

        VertexBuffer* vertexBuffer;
        Effect* effect = effects->get(0);

        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        GLenum buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
        glDrawBuffers(3, buffers);
//        glDrawBuffer(GL_NONE);
//        glReadBuffer(GL_NONE);

        effect->activate();
        
        while (effect->hasNextPass())
        {
            for (auto i = drawCallList.begin(); i != drawCallList.end(); ++i)
            {
                vertexBuffer = vertexBuffers->get(i->vertexBuffer);
                vertexBuffer->render();
            }
            
            effect->gotoNextPass();
        }
        
        effect->deactivate();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // render quad with texture on it
        glEnable(GL_TEXTURE_2D);
        
        glBindTexture(GL_TEXTURE_2D, colorTexture);
        glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex2d(-1, 0);

        glTexCoord2d(1, 0);
        glVertex2d(0, 0);

        glTexCoord2d(1, 1);
        glVertex2d(0, 1);

        glTexCoord2d(0, 1);
        glVertex2d(-1, 1);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, aux0Texture);
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
        
        glBindTexture(GL_TEXTURE_2D, aux1Texture);
        glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex2d(0, -1);

        glTexCoord2d(1, 0);
        glVertex2d(1, -1);

        glTexCoord2d(1, 1);
        glVertex2d(1, 0);

        glTexCoord2d(0, 1);
        glVertex2d(0, 0);
        glEnd();
        
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex2d(-1, -1);

        glTexCoord2d(1, 0);
        glVertex2d(0, -1);

        glTexCoord2d(1, 1);
        glVertex2d(0, 0);

        glTexCoord2d(0, 1);
        glVertex2d(-1, 0);
        glEnd();
        
        check();
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

    void OpenGLRenderer::check()
    {
        auto error = glGetError();

        if (error != 0)
        {
            LOG(FATAL) << "OpenGL error: " << error << std::endl << gluErrorString(error);
        }
    }
}
