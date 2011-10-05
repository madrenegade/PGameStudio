#include "Platform/Editor/GraphicsContext.h"
#include "Utilities/Properties/PropertyManager.h"
#include <Qt/QtOpenGL>

namespace Platform
{
    namespace Editor
    {

        GraphicsContext::GraphicsContext(const std::shared_ptr<Utilities::Properties::PropertyManager>& properties)
        : properties(properties)
        {
            //ctor
        }

        GraphicsContext::~GraphicsContext()
        {
            //dtor
        }

        void GraphicsContext::MakeCurrent()
        {
            QGLWidget* glWidget = properties->get<QGLWidget*>("GL_WIDGET");
            glWidget->makeCurrent();
        }

        void GraphicsContext::Release()
        {

        }

        void GraphicsContext::SwapBuffers()
        {

        }

    } // namespace Editor
} // namespace Platform
