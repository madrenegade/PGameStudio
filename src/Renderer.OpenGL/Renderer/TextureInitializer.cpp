/* 
 * File:   TextureInitializer.cpp
 * Author: madrenegade
 * 
 * Created on September 18, 2011, 6:30 PM
 */

#include "Renderer/TextureInitializer.h"
#include "Renderer/TextureRequest.h"
#include "Renderer/Texture.h"

#include <IL/il.h>

struct ImageDeleter
{
    unsigned int imageID;
    
    void operator()(unsigned char* /*data*/)
    {
        ilBindImage(0);
        ilDeleteImages(1, &imageID);
    }
};

namespace Renderer
{
    void TextureInitializer::initialize(const boost::shared_ptr<Texture>& texture, const TextureRequest& request)
    {
        ImageDeleter deleter;
        
        unsigned int imageID;
        ilGenImages(1, &imageID);
        ilBindImage(imageID);
        
        ilLoadL(IL_JPG, request.file->getData(), request.file->getSize());
        
        deleter.imageID = imageID;
        
        boost::shared_array<unsigned char> data(ilGetData(), deleter);
        unsigned int width = ilGetInteger(IL_IMAGE_WIDTH);
        unsigned int height = ilGetInteger(IL_IMAGE_HEIGHT);
        
        texture->setData(data, width, height);
    }
}
