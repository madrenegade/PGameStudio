#ifndef PLATFORM_EDITOR_GRAPHICSCONTEXT_H
#define PLATFORM_EDITOR_GRAPHICSCONTEXT_H

#include "Graphics/GraphicsContext.h"
#include <memory>

namespace Utilities
{
    namespace Properties
    {
        class PropertyManager;
    }
}

namespace Platform
{
    namespace Editor
    {

        class GraphicsContext : public Graphics::GraphicsContext
        {
        public:
            GraphicsContext(const Utilities::Properties::PropertyManager* const properties);
            virtual ~GraphicsContext();

            virtual void MakeCurrent();
            virtual void Release();
            virtual void SwapBuffers();

        private:
            const Utilities::Properties::PropertyManager* const properties;
        };

    } // namespace Editor
} // namespace Platform

#endif // PLATFORM_EDITOR_GRAPHICSCONTEXT_H
