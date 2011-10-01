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
#include "Renderer/Viewport.h"
#include "Renderer/AnaglyphCompositor.h"
#include "Renderer/DefaultCompositor.h"

#include "Graphics/MonoViewCamera.h"
#include "Graphics/StereoViewCamera.h"

#include "Math/Matrix4.h"
#include "Math/Vector4.h"
#include "Math/Vector3.h"
#include "Math/Quaternion.h"
#include "Math/Vector2.h"
#include "Utilities/Properties/PropertyManager.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <glog/logging.h>
#include <list>
#include <chrono>

using namespace Utilities::Memory;

namespace Renderer
{

    OpenGLRenderer::OpenGLRenderer(const boost::shared_ptr<MemoryManager>& memory,
                                   pool_id pool,
                                   const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties,
                                   const boost::shared_ptr<Manager<VertexBuffer, VertexBufferRequest, VertexBufferInitializer > > &vbManager,
                                   const boost::shared_ptr<Manager<IndexBuffer, IndexBufferRequest, IndexBufferInitializer > > &ibManager,
                                   const boost::shared_ptr<Manager<Effect, EffectRequest, EffectInitializer> >& effectManager,
                                   const boost::shared_ptr<Manager<Texture, TextureRequest, TextureInitializer> >& textureManager)
        : memory(memory), pool(pool), properties(properties), vertexBuffers(vbManager), indexBuffers(ibManager), effects(effectManager), textures(textureManager)
    {
    }

    OpenGLRenderer::~OpenGLRenderer()
    {
        effects->clear();
        Effect::deinitialize();
    }

    void OpenGLRenderer::initialize()
    {
        width = properties->get<unsigned int>("Window.width");
        height = properties->get<unsigned int>("Window.height");
        fieldOfView = properties->get<double>("Graphics.fieldOfView");
        zNear = properties->get<double>("Graphics.zNear");
        zFar = properties->get<double>("Graphics.zFar");

        glewInit();

        Effect::initialize();

        optimizedDrawCalls.reserve(10);

        ErrorHandler::checkForErrors();
    }

    void OpenGLRenderer::setCamera(const boost::shared_ptr<Graphics::Camera>& camera)
    {
        this->camera = camera;

        viewport = memory->construct(Viewport(0, 0, width, height), pool);
        viewport->setCamera(camera);
        viewport->activate();

        boost::shared_ptr<FrameBuffer> frameBuffer = memory->construct(FrameBuffer(memory, pool, 4 * camera->getViewCount(), width, height), pool);
        viewport->attachFrameBuffer(frameBuffer);

//        boost::shared_ptr<MultiViewCompositor> compositor = memory->construct(AnaglyphCompositor(viewport.get(), effects, 2), pool);
        boost::shared_ptr<MultiViewCompositor> compositor = memory->construct(DefaultCompositor(viewport.get(), effects, 3), pool);
        viewport->setCompositor(compositor);
    }

    unsigned long OpenGLRenderer::requestVertexBuffer(const boost::shared_array<Utilities::Memory::byte>& data,
            const unsigned int numVertices, const Graphics::VertexFormat& fmt)
    {
        VertexBufferRequest request;
        request.data = data;
        request.numVertices = numVertices;
        request.format = fmt;

        return vertexBuffers->queueRequest(request);
    }

    unsigned long OpenGLRenderer::requestIndexBuffer(const boost::shared_array<unsigned int>& data, const unsigned int numIndexes)
    {
        IndexBufferRequest request;
        request.data = data;
        request.numIndexes = numIndexes;

        return indexBuffers->queueRequest(request);
    }

    unsigned long OpenGLRenderer::requestEffect(const Utilities::IO::File::Handle& file)
    {
        EffectRequest request;
        request.file = file;

        return effects->queueRequest(request);
    }

    unsigned long OpenGLRenderer::requestTexture(const char* const name, Utilities::IO::File::Handle& file)
    {
        TextureRequest request;
        request.name = name;
        request.file = file;

        return textures->queueRequest(request);
    }

    bool OpenGLRenderer::isTextureRequested(const char* const name)
    {
        return textures->isRequested(name);
    }

    unsigned long OpenGLRenderer::getTexture(const char* const name)
    {
        return textures->getID(name);
    }

    bool OpenGLRenderer::isVertexBufferLoaded(const unsigned long vbID) const
    {
        return vertexBuffers->isLoaded(vbID);
    }

    bool OpenGLRenderer::isIndexBufferLoaded(const unsigned long ibID) const
    {
        return indexBuffers->isLoaded(ibID);
    }

    bool OpenGLRenderer::isEffectLoaded(const unsigned long effectID) const
    {
        return effects->isLoaded(effectID);
    }

    bool OpenGLRenderer::isTextureLoaded(const unsigned long textureID) const
    {
        return textures->isLoaded(textureID);
    }

    void OpenGLRenderer::beginScene()
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->update();
    }

    void OpenGLRenderer::processDrawCalls()
    {
        //DrawCallList drawCallList;

        popDrawCallsTo(optimizedDrawCalls);
        //RAW_VLOG(3, "Draw calls: %i", drawCallList.size());

        const FrameBuffer* fb = viewport->getFrameBuffer();
        fb->bind();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (unsigned int i = 0; i < viewport->getCamera()->getViewCount(); ++i)
        {
            const unsigned int firstAttachment = 4 * i;
            viewport->getCamera()->activateView(i);

            renderToFrameBuffer(optimizedDrawCalls, firstAttachment);
            renderToTexture(i, firstAttachment);
        }

        fb->unbind();

        renderToScreen();

        optimizedDrawCalls.clear();

        ErrorHandler::checkForErrors();
    }

    void OpenGLRenderer::renderToFrameBuffer(const DrawCallList& drawCallList,
            unsigned int firstAttachment)
    {
        GLenum buffers[] = {GL_COLOR_ATTACHMENT0 + firstAttachment, GL_COLOR_ATTACHMENT1 + firstAttachment, GL_COLOR_ATTACHMENT2 + firstAttachment};
        glDrawBuffers(3, buffers);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const Math::Matrix4 view(viewport->getCamera()->getViewMatrix());

        Effect* effect = effects->get(0);

        effect->activate();

        while (effect->hasNextPass())
        {
            renderGeometry(drawCallList, effect, view);
            effect->gotoNextPass();
        }

        effect->deactivate();
    }

    void OpenGLRenderer::renderToTexture(unsigned int /*viewIndex*/,
                                         unsigned int firstAttachment)
    {
        const FrameBuffer* fb = viewport->getFrameBuffer();

        GLenum colorAccumulationBuffers[] = {GL_COLOR_ATTACHMENT3 + firstAttachment};
        glDrawBuffers(1, colorAccumulationBuffers);

        Effect* effect = effects->get(1);
        effect->set("ZNear", zNear);
        effect->set("ZFar", zFar);

        const Texture* colorTexture = fb->getColorAttachment(0 + firstAttachment);
        const Texture* aux0Texture = fb->getColorAttachment(1 + firstAttachment);
        const Texture* aux1Texture = fb->getColorAttachment(2 + firstAttachment);
        const Texture* depthTexture = fb->getDepthAttachment();

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
        getViewVectors(v, viewport->getCamera());

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

        colorTexture->unbind(0);
        aux0Texture->unbind(1);
        aux1Texture->unbind(2);
        depthTexture->unbind(3);
    }

    void OpenGLRenderer::renderToScreen()
    {
        viewport->getCompositor()->startCompose();
        glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex2d(-1, -1);

        glTexCoord2d(1, 0);
        glVertex2d(1, -1);

        glTexCoord2d(1, 1);
        glVertex2d(1, 1);

        glTexCoord2d(0, 1);
        glVertex2d(-1, 1);
        glEnd();

        viewport->getCompositor()->endCompose();
    }

    void OpenGLRenderer::renderGeometry(const DrawCallList& drawCallList, Effect* effect,
                                        const Math::Matrix4& viewMatrix)
    {
        Texture* texture = 0;

        for (auto i = drawCallList.begin(); i != drawCallList.end(); ++i)
        {
            for (auto t = 0u; t < 1; /*i->material->textures.size();*/ ++t)
            {
                texture = textures->get(i->material->textures[t]);
                texture->bind(t);

                effect->set(t, texture);
            }

            effect->set("Diffuse", i->material->diffuse);
            effect->set("Specular", i->material->specular);

            const Math::Matrix4 mv(i->transform * viewMatrix);
            effect->set("ModelView", mv);
            effect->set("ModelViewProjection", mv * (viewport->getCamera()->getProjectionMatrix()));

            vertexBuffers->get(i->vertexBuffer)->render(indexBuffers->get(i->indexBuffer));

            for (auto t = 0u; t != i->material->textures.size(); ++t)
            {
                textures->get(i->material->textures[t])->unbind(t);
            }
        }
    }

    void OpenGLRenderer::getViewVectors(Math::Vector4* v, const Graphics::Camera* camera)
    {
        static const int pixels[4][2] = {
            {0, 0},
            {0, height},
            {width, height},
            {width, 0}
        };

        static const int viewport[4] = {0, 0, width, height};

        const Math::Matrix4 view(camera->getViewMatrix());

        Math::Matrix4 view_rotation(view);
        view_rotation.m14 = 0;
        view_rotation.m24 = 0;
        view_rotation.m34 = 0;

        double d[3];

        for (int i = 0; i < 4; ++i)
        {
            gluUnProject(pixels[i][0], pixels[i][1], 1,
                         view, this->viewport->getCamera()->getProjectionMatrix(), viewport,
                         &d[0], &d[1], &d[2]);

            v[i] = Math::Vector4(d[0], d[1], d[2], 0);
            v[i] -= Math::Vector4(camera->getPosition(), 0);
            v[i].Normalize();
            v[i] *= view_rotation;

            //            LOG(INFO) << "v[" << i << "] " << v[i].X << ", " << v[i].Y << ", " << v[i].Z;
        }
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

    void OpenGLRenderer::popDrawCallsTo(DrawCallList& drawCallList)
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
}
