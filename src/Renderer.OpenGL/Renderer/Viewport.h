/* 
 * File:   Viewport.h
 * Author: madrenegade
 *
 * Created on September 25, 2011, 8:52 PM
 */

#ifndef RENDERER_VIEWPORT_H
#define RENDERER_VIEWPORT_H

namespace Renderer
{

    class Viewport
    {
    public:
        Viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
        ~Viewport();
        
        void activate() const;
        
    private:
        const unsigned int x;
        const unsigned int y;
        const unsigned int width;
        const unsigned int height;
    };
}


#endif	/* RENDERER_VIEWPORT_H */

