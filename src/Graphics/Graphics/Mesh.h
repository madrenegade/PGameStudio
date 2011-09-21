/* 
 * File:   Mesh.h
 * Author: madrenegade
 *
 * Created on September 21, 2011, 10:25 AM
 */

#ifndef GRAPHICS_MESH_H
#define	GRAPHICS_MESH_H

#include "Graphics/Material.h"

namespace Graphics
{
    struct Mesh
    {
        unsigned long vertexBuffer;
        unsigned long indexBuffer;
        
        boost::shared_ptr<Material> material;
    };
}

#endif	/* GRAPHICS_MESH_H */

