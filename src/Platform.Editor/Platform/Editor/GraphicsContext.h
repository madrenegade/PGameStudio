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
            GraphicsContext(const std::shared_ptr<Utilities::Properties::PropertyManager>& properties);
            virtual ~GraphicsContext();

            virtual void MakeCurrent();
            virtual void Release();
            virtual void SwapBuffers();

        private:
            const std::shared_ptr<Utilities::Properties::PropertyManager> properties;
        };

    } // namespace Editor
} // namespace Platform

#endif // PLATFORM_EDITOR_GRAPHICSCONTEXT_H
