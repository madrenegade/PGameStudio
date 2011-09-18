/* 
 * File:   Material.h
 * Author: madrenegade
 *
 * Created on September 17, 2011, 9:35 AM
 */

#ifndef GRAPHICS_MATERIAL_H
#define	GRAPHICS_MATERIAL_H

#include <vector>

namespace Graphics
{

    struct Material
    {
        unsigned long effect;
        
        std::vector<unsigned long> textures;
    };
}

#endif	/* GRAPHICS_MATERIAL_H */

