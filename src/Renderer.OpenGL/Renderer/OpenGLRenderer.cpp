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
#include "Renderer/FrameBuffer.h"
#include "Renderer/ErrorHandler.h"

#include "Graphics/Camera.h"

#include "Math/Matrix4.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/Vector2.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <glog/logging.h>
#include <list>
#include <chrono>

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
        Effect::deinitialize();
    }

    void OpenGLRenderer::initialize()
    {
        width = 800;
        height = 600;
        fieldOfView = 60.0;
        zNear = 0.1;
        zFar = 100.0;
        
        glewInit();
        glViewport(0, 0, width, height);
        
        projection.reset(new Math::Matrix4(Math::Matrix4::CreatePerspectiveFieldOfView(Math::PI * fieldOfView / 180.0, static_cast<double>(width) / static_cast<double>(height), zNear, zFar)));

        frameBuffer.reset(new FrameBuffer(3, width, height));
        
        Effect::initialize();

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

    void OpenGLRenderer::processDrawCalls(const std::vector<Graphics::Camera>& cameras)
    {
        std::list<Graphics::DrawCall> drawCallList;
        popDrawCallsTo(drawCallList);

        for (unsigned int i = 0; i < cameras.size(); ++i)
        {
            renderToFrameBuffer(drawCallList, cameras.at(i));
            renderToScreen(cameras.at(i));
        }

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

    void OpenGLRenderer::popDrawCallsTo(std::list<Graphics::DrawCall>& drawCallList)
    {
        Graphics::DrawCall drawCall;
        while (!drawCalls.empty())
        {
            if (drawCalls.try_pop(drawCall))
            {
                drawCallList.push_back(drawCall);
            }
        }
    }

    typedef std::chrono::duration<double, std::ratio < 1, 1 >> sec;
    
    void OpenGLRenderer::renderToFrameBuffer(const std::list<Graphics::DrawCall>& drawCallList,
                                             const Graphics::Camera& camera)
    {
        frameBuffer->bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
        glDrawBuffers(3, buffers);
        
        static double t = 0.0;
        const Math::Quaternion rot(0, 1, 0, std::sin(t));
        t += 0.0001;
        
        const Math::Matrix4 transform(Math::Matrix4::CreateTransform(Math::Vector3(), rot));
        const Math::Matrix4 view(camera.getViewMatrix());
        
        const Math::Matrix4 mv(transform * view);

        Effect* effect = effects->get(0);
        effect->set("ModelView", mv);
        effect->set("ModelViewProjection", mv * (*projection));
        effect->activate();

        while (effect->hasNextPass())
        {
            renderGeometry(drawCallList, effect);
            effect->gotoNextPass();
        }

        effect->deactivate();

        frameBuffer->unbind();
    }

    void OpenGLRenderer::renderToScreen(const Graphics::Camera& camera)
    {
        Effect* effect = effects->get(1);
        effect->set("ZNear", zNear);
        effect->set("ZFar", zFar);

        const Texture* colorTexture = frameBuffer->getColorAttachment(0);
        const Texture* aux0Texture = frameBuffer->getColorAttachment(1);
        const Texture* aux1Texture = frameBuffer->getColorAttachment(2);
        const Texture* depthTexture = frameBuffer->getDepthAttachment();

        colorTexture->bind(0);
        effect->set(0, colorTexture);

        aux0Texture->bind(1);
        effect->set(1, aux0Texture);

        aux1Texture->bind(2);
        effect->set(2, aux1Texture);

        depthTexture->bind(3);
        effect->set(3, depthTexture);

        effect->activate();

        Math::Vector4 v[4];
        getViewVectors(v, camera);

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
    }

    void OpenGLRenderer::renderGeometry(const std::list<Graphics::DrawCall>& drawCallList, Effect* effect)
    {
        Texture* texture = 0;

        for (auto i = drawCallList.begin(); i != drawCallList.end(); ++i)
        {
            for (auto t = 0; t != i->material->textures.size(); ++t)
            {
                texture = textures->get(i->material->textures[t]);
                texture->bind(t);

                effect->set(t, texture);
            }

            vertexBuffers->get(i->vertexBuffer)->render(indexBuffers->get(i->indexBuffer));

            for (auto t = 0; t != i->material->textures.size(); ++t)
            {
                textures->get(i->material->textures[t])->unbind(t);
            }
        }
    }

    void OpenGLRenderer::getViewVectors(Math::Vector4* v, const Graphics::Camera& camera)
    {
        static const int pixels[4][2] = {
            {0, 0},
            {0, height},
            {width, height},
            {width, 0}
        };

        static const int viewport[4] = {0, 0, width, height};

        const Math::Matrix4 view(camera.getViewMatrix());

        Math::Matrix4 view_rotation(view);
        view_rotation.M14(0);
        view_rotation.M24(0);
        view_rotation.M34(0);

        double d[3];

        for (int i = 0; i < 4; ++i)
        {
            gluUnProject(pixels[i][0], pixels[i][1], 1,
                view, *projection, viewport,
                &d[0], &d[1], &d[2]);

            v[i] = Math::Vector4(d[0], d[1], d[2], 0);
            v[i] -= Math::Vector4(camera.getPosition(), 0);
            v[i].Normalize();
            v[i] *= view_rotation;
        }
    }
}
