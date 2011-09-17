/* 
 * File:   Renderer.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 9:09 PM
 */

#include "Graphics/Renderer.h"
#include "Graphics/DrawCall.h"

namespace Graphics
{

    Renderer::Renderer()
    {
    }

    Renderer::~Renderer()
    {
    }
    
    void Renderer::processRequests()
    {
        processVertexBufferRequests();
        processEffectRequests();
    }
    
    void Renderer::pushDrawCall(const DrawCall& drawCall)
    {
        drawCalls.push(drawCall);
    }
}
