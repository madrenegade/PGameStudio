/* 
 * File:   Texture.cpp
 * Author: madrenegade
 * 
 * Created on September 18, 2011, 6:39 PM
 */

#include "Renderer/Texture.h"

#include <glog/logging.h>
#include <GL/glew.h>

namespace Renderer
{
    struct TextureDeleter
    {
        void operator()(unsigned int* id)
        {
            glDeleteTextures(1, id);
            delete id;
        }
    };

    Texture::Texture()
    {
        id.reset(new unsigned int, TextureDeleter());
        glGenTextures(1, id.get());
    }

    Texture::~Texture()
    {
        
    }

    void Texture::setData(const boost::shared_array<unsigned char>& data, unsigned int w, unsigned int h)
    {
        glBindTexture(GL_TEXTURE_2D, *id);

        glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data.get());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::bind(unsigned int level) const
    {
        glActiveTexture(GL_TEXTURE0 + level);
        glBindTexture(GL_TEXTURE_2D, *id);
    }

    void Texture::unbind(unsigned int level) const
    {
        glActiveTexture(GL_TEXTURE0 + level);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    unsigned int Texture::getID() const
    {
        return *id;
    }
}
