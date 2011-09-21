/* 
 * File:   Material.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 9:35 AM
 */

#ifndef GRAPHICS_MATERIAL_H
#define	GRAPHICS_MATERIAL_H

#include <vector>
#include "Math/Vector4.h"

namespace Graphics
{

    struct Material
    {
        Math::Vector4 diffuse;
        Math::Vector4 specular;
        
        std::vector<unsigned long> textures;
    };
}

#endif	/* GRAPHICS_MATERIAL_H */

