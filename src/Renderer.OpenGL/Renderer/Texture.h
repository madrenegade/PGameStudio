/* 
 * File:   Texture.h
 * Author: madrenegade
 *
 * Created on September 18, 2011, 6:39 PM
 */

#ifndef RENDERER_TEXTURE_H
#define	RENDERER_TEXTURE_H

#include <boost/shared_array.hpp>

namespace Renderer
{

    class Texture
    {
    public:
        Texture();
        ~Texture();
        
        void setData(const boost::shared_array<unsigned char>& data, unsigned int w, unsigned int h);
        
        void bind(unsigned int level = 0);
        void unbind(unsigned int level = 0);
        
        unsigned int getID() const;
        
    private:
        unsigned int id;
    };
}

#endif	/* RENDERER_TEXTURE_H */

