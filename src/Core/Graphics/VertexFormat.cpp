/* 
 * File:   VertexFormat.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 9:42 PM
 */

#include "Graphics/VertexFormat.h"

namespace Graphics
{

    VertexFormat::VertexFormat()
    {
    }

    VertexFormat::~VertexFormat()
    {
    }
    
    const unsigned int VertexFormat::vertexSize() const
    {
        return 3 * sizeof(double);
    }
}
