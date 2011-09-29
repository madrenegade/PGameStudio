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
                               ptrdiff_t normalOffset, size_t normalSize,
                               ptrdiff_t tangentOffset, size_t tangentSize,
                               ptrdiff_t bitangentOffset, size_t bitangentSize)
    : vertexSize(vertexSize), positionOffset(positionOffset), positionSize(positionSize),
    texCoordOffset(texCoordOffset), texCoordSize(texCoordSize),
    normalOffset(normalOffset), normalSize(normalSize),
    tangentOffset(tangentOffset), tangentSize(tangentSize),
    bitangentOffset(bitangentOffset), bitangentSize(bitangentSize)
    {
    }

    VertexFormat::~VertexFormat()
    {
    }

    size_t VertexFormat::getVertexSize() const
    {
        return vertexSize;
    }

    ptrdiff_t VertexFormat::getPositionOffset() const
    {
        return positionOffset;
    }

    size_t VertexFormat::getPositionSize() const
    {
        return positionSize;
    }

    bool VertexFormat::hasTexCoords() const
    {
        return texCoordSize != 0;
    }

    ptrdiff_t VertexFormat::getTexCoordOffset() const
    {
        return texCoordOffset;
    }

    size_t VertexFormat::getTexCoordSize() const
    {
        return texCoordSize;
    }

    bool VertexFormat::hasNormal() const
    {
        return normalSize != 0;
    }

    ptrdiff_t VertexFormat::getNormalOffset() const
    {
        return normalOffset;
    }

    size_t VertexFormat::getNormalSize() const
    {
        return normalSize;
    }
    
    bool VertexFormat::hasTangent() const
    {
        return tangentSize != 0;
    }

    ptrdiff_t VertexFormat::getTangentOffset() const
    {
        return tangentOffset;
    }

    size_t VertexFormat::getTangentSize() const
    {
        return tangentSize;
    }
    
    bool VertexFormat::hasBitangent() const
    {
        return bitangentSize != 0;
    }

    ptrdiff_t VertexFormat::getBitangentOffset() const
    {
        return bitangentOffset;
    }

    size_t VertexFormat::getBitangentSize() const
    {
        return bitangentSize;
    }
}
