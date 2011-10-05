#include "Platform/Editor/Window.h"
#include "Platform/Editor/GraphicsContext.h"

namespace Platform
{
    namespace Editor
    {

        Window::Window(const Utilities::Properties::PropertyManager* const properties)
        : context(new GraphicsContext(properties))
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
