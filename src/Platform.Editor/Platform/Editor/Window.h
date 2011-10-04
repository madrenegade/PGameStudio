#ifndef PLATFORM_EDITOR_WINDOW_H
#define PLATFORM_EDITOR_WINDOW_H

#include "Graphics/Window.h"
#include <boost/shared_ptr.hpp>

namespace Platform
{
    namespace Editor
    {
        class GraphicsContext;

        class Window : public Graphics::Window
        {
        public:
            Window(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
            virtual ~Window();

            virtual Graphics::GraphicsContext* getGraphicsContext() const;

        private:
            boost::shared_ptr<GraphicsContext> context;
        };

    } // namespace Editor
} // namespace Platform

#endif // PLATFORM_EDITOR_WINDOW_H
