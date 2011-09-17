/* 
 * File:   DrawCall.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 9:22 AM
 */

#ifndef GRAPHICS_DRAWCALL_H
#define	GRAPHICS_DRAWCALL_H

#include "Material.h"

namespace Graphics
{
    struct DrawCall
    {
        unsigned long vertexBuffer;
        Material* material;
    };
}

#endif	/* GRAPHICS_DRAWCALL_H */

