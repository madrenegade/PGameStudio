/* 
 * File:   GraphicsContext.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 3:31 PM
 */

#ifndef GRAPHICS_GRAPHICSCONTEXT_H
#define	GRAPHICS_GRAPHICSCONTEXT_H

namespace Graphics
{

    class GraphicsContext
    {
    public:
        
        /**
         * Makes this graphics context current in this thread
         */
        virtual void MakeCurrent() = 0;
        
        /**
         * Opposite of MakeCurrent
         */
        virtual void Release() = 0;
        
        virtual void SwapBuffers() = 0;
        
        virtual ~GraphicsContext();
        
    protected:
        GraphicsContext();
    };
}

#endif	/* GRAPHICS_GRAPHICSCONTEXT_H */

