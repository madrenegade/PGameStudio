#ifndef GRAPHICS_RENDERTASK_H
#define GRAPHICS_RENDERTASK_H

#include <tbb/task.h>

namespace Graphics
{
    class GraphicsContext;
    class Renderer;
    class SceneNode;

    class RenderTask : public tbb::task
    {
    public:
        RenderTask(Renderer* renderer, GraphicsContext* context, SceneNode* scene);
        virtual ~RenderTask();

        virtual tbb::task* execute();

    private:
        Renderer* renderer;
        GraphicsContext* context;
        SceneNode* scene;
    };
}

#endif // GRAPHICS_RENDERTASK_H
