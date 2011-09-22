/* 
 * File:   DrawCall.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 9:22 AM
 */

#ifndef GRAPHICS_DRAWCALL_H
#define	GRAPHICS_DRAWCALL_H

#include "Material.h"
#include "Math/Matrix4.h"

namespace Graphics
{
    struct DrawCall
    {
        Math::Matrix4 transform;
        
        unsigned long vertexBuffer;
        unsigned long indexBuffer;
        Material* material;
    };
}

#endif	/* GRAPHICS_DRAWCALL_H */

