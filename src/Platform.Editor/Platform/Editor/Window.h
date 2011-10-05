#ifndef PLATFORM_EDITOR_WINDOW_H
#define PLATFORM_EDITOR_WINDOW_H

#include "Graphics/Window.h"


namespace Platform
{
    namespace Editor
    {
        class GraphicsContext;

        class Window : public Graphics::Window
        {
        public:
            Window(const Utilities::Properties::PropertyManager* const properties);
            virtual ~Window();

            virtual Graphics::GraphicsContext* getGraphicsContext() const;

        private:
            std::shared_ptr<GraphicsContext> context;
        };

    } // namespace Editor
} // namespace Platform

#endif // PLATFORM_EDITOR_WINDOW_H
