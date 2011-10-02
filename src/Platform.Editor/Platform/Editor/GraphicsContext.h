#ifndef PLATFORM_EDITOR_GRAPHICSCONTEXT_H
#define PLATFORM_EDITOR_GRAPHICSCONTEXT_H

#include "Graphics/GraphicsContext.h"

namespace Platform
{
    namespace Editor
    {

        class GraphicsContext : public Graphics::GraphicsContext
        {
        public:
            GraphicsContext();
            virtual ~GraphicsContext();

            virtual void MakeCurrent();
            virtual void Release();
            virtual void SwapBuffers();

        };

    } // namespace Editor
} // namespace Platform

#endif // PLATFORM_EDITOR_GRAPHICSCONTEXT_H
