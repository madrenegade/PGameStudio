#ifndef GRAPHICS_RENDERTASK_H
#define GRAPHICS_RENDERTASK_H

#include <tbb/task.h>

    namespace Graphics
    {
        class RenderTask : public tbb::task
        {
        public:
            RenderTask();
            virtual ~RenderTask();

            virtual tbb::task* execute();
        };
    }

#endif // GRAPHICS_RENDERTASK_H
