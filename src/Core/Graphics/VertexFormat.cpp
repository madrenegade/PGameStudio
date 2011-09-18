/* 
 * File:   VertexFormat.cpp
 * Author: madrenegade
 * 
 * Created on September 16, 2011, 9:42 PM
 */

#include "Graphics/VertexFormat.h"

namespace Graphics
{

    VertexFormat::VertexFormat(size_t vertexSize,
                     ptrdiff_t positionOffset, size_t positionSize,
                     ptrdiff_t texCoordOffset, size_t texCoordSize,
                     ptrdiff_t normalOffset, size_t normalSize)
    : vertexSize(vertexSize), positionOffset(positionOffset), positionSize(positionSize),
    texCoordOffset(texCoordOffset), texCoordSize(texCoordSize),
    normalOffset(normalOffset), normalSize(normalSize)
    {
    }

    VertexFormat::~VertexFormat()
    {
    }

    const size_t VertexFormat::getVertexSize() const
    {
        return vertexSize;
    }

    const ptrdiff_t VertexFormat::getPositionOffset() const
    {
        return positionOffset;
    }

    const size_t VertexFormat::getPositionSize() const
    {
        return positionSize;
    }

    bool VertexFormat::hasTexCoords() const
    {
        return texCoordSize != 0;
    }
    
    const ptrdiff_t VertexFormat::getTexCoordOffset() const
    {
        return texCoordOffset;
    }

    const size_t VertexFormat::getTexCoordSize() const
    {
        return texCoordSize;
    }
    
    bool VertexFormat::hasNormal() const
    {
        return normalSize != 0;
    }

    const ptrdiff_t VertexFormat::getNormalOffset() const
    {
        return normalOffset;
    }

    const size_t VertexFormat::getNormalSize() const
    {
        return normalSize;
    }
}
