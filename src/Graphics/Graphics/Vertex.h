/* 
 * File:   TexturedVertex.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 9:18 AM
 */

#ifndef GRAPHICS_VERTEX_H
#define	GRAPHICS_VERTEX_H

#include "Math/Vector3.h"
#include "Math/Vector2.h"

namespace Graphics
{
    struct TexturedVertex
    {
        Math::Vector3 position;
        Math::Vector2 texcoords;
    };
    
    struct TexturedVertexWithNormal
    {
        Math::Vector3 position;
        Math::Vector2 texcoords;
        Math::Vector3 normal;
    };
    
    struct VertexTNBT
    {
        Math::Vector3 position;
        Math::Vector2 texcoords;
        Math::Vector3 normal;
        Math::Vector3 tangent;
        Math::Vector3 bitangent;
    };
}

#endif	/* GRAPHICS_VERTEX_H */

