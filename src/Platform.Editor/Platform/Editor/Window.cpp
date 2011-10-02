#include "Platform/Editor/Window.h"
#include "Platform/Editor/GraphicsContext.h"

namespace Platform
{
    namespace Editor
    {

        Window::Window()
        {
            //ctor
        }

        Window::~Window()
        {
            //dtor
        }

        Graphics::GraphicsContext* Window::getGraphicsContext() const
        {
            return context.get();
        }

    } // namespace Editor
} // namespace Platform
