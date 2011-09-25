/* 
 * File:   GlxGraphicsContext.h
 * Author: madrenegade
 *
 * Created on November 29, 2010, 4:36 PM
 */

#ifndef PLATFORM_LINUX_GLXGRAPHICSCONTEXT_H
#define	PLATFORM_LINUX_GLXGRAPHICSCONTEXT_H

#include "Graphics/GraphicsContext.h"
#include <GL/glx.h>

namespace Platform
{
    namespace Linux
    {

        class GLXGraphicsContext : public Graphics::GraphicsContext
        {
        public:
            static GLXGraphicsContext* Create(Display* pDisplay,
                                              Window window,
                                              GLXFBConfig fbConfig);

            virtual ~GLXGraphicsContext();

            virtual void MakeCurrent();
            virtual void Release();
            virtual void SwapBuffers();

        private:
            static GLXGraphicsContext* CreateInternalContext(Display* pDisplay, Window window, GLXFBConfig fbConfig);
            
            GLXGraphicsContext(Display* pDisplay, Window window, GLXContext context);

            Display* m_pDisplay;
            Window m_windowHandle;
            GLXContext m_context;
        };
    }
}


#endif	/* PLATFORM_LINUX_GLXGRAPHICSCONTEXT_H */

