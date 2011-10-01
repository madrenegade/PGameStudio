#include "Graphics/RenderTask.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Graphics/SceneNode.h"

#include <glog/logging.h>

namespace Graphics
{

    RenderTask::RenderTask(Renderer* renderer, GraphicsContext* context, SceneNode* scene)
        : renderer(renderer), context(context), scene(scene)
    {
    }

    RenderTask::~RenderTask()
    {
    }

    tbb::task* RenderTask::execute()
    {
        context->MakeCurrent();

        renderer->processRequests();

        renderer->beginScene();

        scene->prepare(renderer);

        renderer->processDrawCalls();

        context->SwapBuffers();
        context->Release();

        return 0;
    }
}
