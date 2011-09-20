#include "Graphics/RenderTask.h"
#include "Graphics/GraphicsContext.h"
#include "Graphics/Renderer.h"
#include "Graphics/Camera.h"
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
        std::vector<Camera> cams;
        cams.push_back(Camera(Math::Vector3(4, 2, 4), Math::Vector3(0, 0, 0)));
        
        context->MakeCurrent();
        
        renderer->processRequests();
        
        renderer->beginScene();
        
        scene->prepare(renderer);
        
        renderer->processDrawCalls(cams);
        
        context->SwapBuffers();
        context->Release();

        return 0;
    }
}
