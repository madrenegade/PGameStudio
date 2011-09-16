#ifndef GRAPHICS_RENDERTASK_H
#define GRAPHICS_RENDERTASK_H

#include <tbb/task.h>

    namespace Graphics
    {
        class GraphicsContext;
        
        class RenderTask : public tbb::task
        {
        public:
            RenderTask(GraphicsContext* context);
            virtual ~RenderTask();

            virtual tbb::task* execute();
            
        private:
            GraphicsContext* context;
        };
    }

#endif // GRAPHICS_RENDERTASK_H
