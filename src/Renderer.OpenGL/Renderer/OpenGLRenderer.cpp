/* 
 * File:   OpenGLRenderer.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 9:22 PM
 */

#include "Renderer/OpenGLRenderer.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Effect.h"
#include "Renderer/Texture.h"

#include "Renderer/ErrorHandler.h"
#include "Math/Matrix4.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <glog/logging.h>
#include <list>

namespace Renderer
{

    OpenGLRenderer::OpenGLRenderer(const boost::shared_ptr<Manager<VertexBuffer, VertexBufferRequest, VertexBufferInitializer > > &vbManager,
                                   const boost::shared_ptr<Manager<IndexBuffer, IndexBufferRequest, IndexBufferInitializer > > &ibManager,
                                   const boost::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer> >& effectManager,
                                   const boost::shared_ptr<Manager<Texture, TextureRequest, TextureInitializer> >& textureManager)
    : vertexBuffers(vbManager), indexBuffers(ibManager), effects(effectManager), textures(textureManager)
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

        ErrorHandler::checkForErrors();

        VLOG(2) << "creating framebuffer";

        glGenFramebuffers(1, &frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

        GLint maxbuffers;
        glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxbuffers);

        VLOG(2) << "Max render targets: " << maxbuffers;
        ErrorHandler::checkForErrors();

        VLOG(2) << "Create color texture";
        glGenTextures(1, &colorTexture);
        glBindTexture(GL_TEXTURE_2D, colorTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        ErrorHandler::checkForErrors();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

        VLOG(2) << "create aux0 texture";
        glGenTextures(1, &aux0Texture);
        glBindTexture(GL_TEXTURE_2D, aux0Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        ErrorHandler::checkForErrors();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, aux0Texture, 0);

        VLOG(2) << "create aux1 texture";
        glGenTextures(1, &aux1Texture);
        glBindTexture(GL_TEXTURE_2D, aux1Texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 800, 600, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        ErrorHandler::checkForErrors();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, aux1Texture, 0);

        VLOG(2) << "creating depth buffer";
        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 800, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        ErrorHandler::checkForErrors();

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);

        //        glGenRenderbuffers(1, &depthBuffer);
        //        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        //        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, 800, 600);
        //        check();
        //
        //        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
        //        check();


        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            LOG(FATAL) << "Frame buffer status incomplete";
        }

        glDrawBuffer(GL_NONE);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ErrorHandler::checkForErrors();
    }

    unsigned long OpenGLRenderer::requestVertexBuffer(const boost::shared_array<Utilities::Memory::byte>& data,
                                                      unsigned int numVertices, const Graphics::VertexFormat& fmt)
    {
        VertexBufferRequest request;
        request.data = data;
        request.numVertices = numVertices;
        request.format = fmt;
        
        return vertexBuffers->queueRequest(request);
    }

    unsigned long OpenGLRenderer::requestIndexBuffer(const boost::shared_array<unsigned short>& data, unsigned int numIndexes)
    {
        IndexBufferRequest request;
        request.data = data;
        request.numIndexes = numIndexes;
        
        return indexBuffers->queueRequest(request);
    }

    unsigned long OpenGLRenderer::requestEffect(const Utilities::IO::File& file)
    {
        EffectRequest request;
        request.file = file;
        
        return effects->queueRequest(request);
    }
    
    unsigned long OpenGLRenderer::requestTexture(const Utilities::IO::File& file)
    {
        TextureRequest request;
        request.file = file;
        
        return textures->queueRequest(request);
    }

    bool OpenGLRenderer::isVertexBufferLoaded(unsigned long vbID) const
    {
        return vertexBuffers->isLoaded(vbID);
    }

    bool OpenGLRenderer::isIndexBufferLoaded(unsigned long ibID) const
    {
        return indexBuffers->isLoaded(ibID);
    }

    bool OpenGLRenderer::isEffectLoaded(unsigned long effectID) const
    {
        return effects->isLoaded(effectID);
    }
    
    bool OpenGLRenderer::isTextureLoaded(unsigned long textureID) const
    {
        return textures->isLoaded(textureID);
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

        VertexBuffer* vertexBuffer = 0;
        IndexBuffer* indexBuffer = 0;
        Effect* effect = effects->get(0);

        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
        glDrawBuffers(3, buffers);

        effect->activate();

        while (effect->hasNextPass())
        {
            for (auto i = drawCallList.begin(); i != drawCallList.end(); ++i)
            {
                vertexBuffer = vertexBuffers->get(i->vertexBuffer);
                indexBuffer = indexBuffers->get(i->indexBuffer);
                
                unsigned char texLevel = 0;
                for(auto t = i->material->textures.begin(); t != i->material->textures.end(); ++t)
                {
                    char textureName[] = {'T', 'E', 'X', static_cast<unsigned char>(texLevel + 48), '\0'};
                    Texture* texture = textures->get(*t);
                    texture->bind(texLevel);
                    effect->setTexture(textureName, texture->getID());
                    ++texLevel;
                }
                
                vertexBuffer->render(indexBuffer);
                
                texLevel = 0;
                for(auto t = i->material->textures.begin(); t != i->material->textures.end(); ++t)
                {
                    Texture* texture = textures->get(*t);
                    texture->unbind(texLevel);
                    ++texLevel;
                }
            }

            effect->gotoNextPass();
        }

        effect->deactivate();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        effect = effects->get(1);
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorTexture);
        effect->setTexture("TEX0", colorTexture);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, aux0Texture);
        effect->setTexture("TEX1", aux0Texture);
        
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, aux1Texture);
        effect->setTexture("TEX2", aux1Texture);
        
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        effect->setTexture("TEX3", depthTexture);
        
        effect->activate();
        
        int sx = 800;
        int sy = 600;
        
        int pixels[4][2] = 
        {
            {0, 0},
            {0, sy},
            {sx, sy},
            {sx, 0}
        };
        
        int viewport[4] = {0, 0, sx, sy};
        
        const Math::Vector3 camera(4, 4, 4);
        const Math::Matrix4 projection = Math::Matrix4::CreatePerspectiveFieldOfView(3.1415 * 60.0 / 180.0, 16.0 / 9.0, 0.1, 100);
        const Math::Matrix4 view = Math::Matrix4::LookAt(camera, Math::Vector3(0, 0, 0), Math::Vector3(0, 1, 0));
        
        Math::Matrix4 view_rotation = view;
        view_rotation.M41(0);
        view_rotation.M42(0);
        view_rotation.M43(0);
        
        Math::Vector3 v[4];
        double d[3];
        
        for(int i = 0; i < 4; ++i)
        {
            gluUnProject(pixels[i][0], pixels[i][1], 1,
                view, projection, viewport,
                &d[0], &d[1], &d[2]);
            
            v[i] = Math::Vector3(d[0], d[1], d[2]);
            v[i] -= camera;
            v[i].Normalize();
            //v[i] *= view;
        }
        
        glBegin(GL_QUADS);
        glMultiTexCoord2d(GL_TEXTURE0, 0, 0);
        glMultiTexCoord3d(GL_TEXTURE1, v[0].X, v[0].Y, v[0].Z);
        glVertex2d(-1, -1);

        glMultiTexCoord2d(GL_TEXTURE0, 1, 0);
        glMultiTexCoord3d(GL_TEXTURE1, v[1].X, v[1].Y, v[1].Z);
        glVertex2d(1, -1);

        glMultiTexCoord2d(GL_TEXTURE0, 1, 1);
        glMultiTexCoord3d(GL_TEXTURE1, v[2].X, v[2].Y, v[2].Z);
        glVertex2d(1, 1);

        glMultiTexCoord2d(GL_TEXTURE0, 0, 1);
        glMultiTexCoord3d(GL_TEXTURE1, v[3].X, v[3].Y, v[3].Z);
        glVertex2d(-1, 1);
        glEnd();
        
        effect->deactivate();

        ErrorHandler::checkForErrors();
    }

    void OpenGLRenderer::processVertexBufferRequests()
    {
        vertexBuffers->processRequests();
    }

    void OpenGLRenderer::processIndexBufferRequests()
    {
        indexBuffers->processRequests();
    }

    void OpenGLRenderer::processEffectRequests()
    {
        effects->processRequests();
    }
    
    void OpenGLRenderer::processTextureRequests()
    {
        textures->processRequests();
    }
}
