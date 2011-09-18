#include "Renderer/ErrorHandler.h"

#include <cassert>
#include <glog/logging.h>
#include <GL/glew.h>
#include <GL/glu.h>

namespace Renderer
{

    ErrorHandler::ErrorHandler()
    {
        //ctor
    }

    ErrorHandler::~ErrorHandler()
    {
        //dtor
    }

    void ErrorHandler::checkForErrors()
    {
        int error = glGetError();
        
        if(error != GL_NO_ERROR)
        {
            LOG(FATAL) << "OpenGL Error: " << gluErrorString(error);
        }
    }
} // namespace Renderer
