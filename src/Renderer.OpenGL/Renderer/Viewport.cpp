/* 
 * File:   Viewport.cpp
 * Author: madrenegade
 * 
 * Created on September 25, 2011, 8:52 PM
 */

#include "Renderer/Viewport.h"

#include <GL/gl.h>

namespace Renderer
{

    Viewport::Viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
    : x(x), y(y), width(width), height(height)
    {
    }

    Viewport::~Viewport()
    {
    }
    
    void Viewport::activate() const
    {
        glViewport(x, y, width, height);
    }
}
