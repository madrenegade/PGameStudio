#ifndef GRAPHICS_RENDERTASK_H
#define GRAPHICS_RENDERTASK_H

#include <tbb/task.h>

    namespace Graphics
    {
        class GraphicsContext;
        class Renderer;
        
        class RenderTask : public tbb::task
        {
        public:
            RenderTask(Renderer* renderer, GraphicsContext* context);
            virtual ~RenderTask();

            virtual tbb::task* execute();
            
        private:
            Renderer* renderer;
            GraphicsContext* context;
        };
    }

#endif // GRAPHICS_RENDERTASK_H
