#include "Platform/Editor/Window.h"
#include "Platform/Editor/GraphicsContext.h"

namespace Platform
{
    namespace Editor
    {

        Window::Window(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties)
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
