#include "Graphics/RenderTask.h"

namespace Graphics
{

    RenderTask::RenderTask()
    {
    }

    RenderTask::~RenderTask()
    {
    }

    tbb::task* RenderTask::execute()
    {
//        this->m_pRenderer->BeginScene();
//
//        // TODO (madrenegade#1#): Use parallel_for to prepare children of root node
//        this->m_pRootNode->Prepare(this->m_pRenderer);
//        this->m_pRenderer->RenderScene();
//        this->m_pRenderer->EndScene();

        return 0;
    }
}
