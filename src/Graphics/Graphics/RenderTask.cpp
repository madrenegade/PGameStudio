#include "Graphics/RenderTask.h"
#include "Graphics/GraphicsContext.h"

#include <glog/logging.h>

namespace Graphics
{

    RenderTask::RenderTask(GraphicsContext* context)
    : context(context)
    {
    }

    RenderTask::~RenderTask()
    {
    }

    tbb::task* RenderTask::execute()
    {
        context->MakeCurrent();
        
        context->SwapBuffers();
        context->Release();
        // do frustum culling
        // create draw calls
        // begin scene
        // process draw calls
        // end scene
        
//        this->m_pRenderer->BeginScene();
//
//        // TODO (madrenegade#1#): Use parallel_for to prepare children of root node
//        this->m_pRootNode->Prepare(this->m_pRenderer);
//        this->m_pRenderer->RenderScene();
//        this->m_pRenderer->EndScene();

        return 0;
    }
}
