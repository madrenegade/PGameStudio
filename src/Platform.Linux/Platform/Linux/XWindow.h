/* 
 * File:   X11Window.h
 * Author: madrenegade
 *
 * Created on November 29, 2010, 4:36 PM
 */

#ifndef PLATFORM_LINUX_XWINDOW_H
#define	PLATFORM_LINUX_XWINDOW_H

#include "Graphics/Window.h"
#include <GL/glx.h>

namespace Utilities
{
    namespace Memory
    {
        class MemoryManager;
    }
}

namespace Platform
{
    namespace Linux
    {

        class XWindow : public Graphics::Window
        {
        public:
            XWindow(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memory, 
                    unsigned int width, unsigned int height, unsigned int bpp, bool fullscreen);
            
            virtual ~XWindow();
            
            virtual Graphics::GraphicsContext* getGraphicsContext() const;

        private:
            boost::shared_ptr<Graphics::GraphicsContext> m_pGraphicsContext;
            
            Display* display;
            GLXFBConfig fbConfig;
            Colormap cmap;
            ::Window window;
            
            void openDisplay();
            void findFrameBufferConfiguration();
            
            void createWindow(unsigned int width, unsigned int height, bool fullscreen);
        };
    }
}


#endif	/* PLATFORM_LINUX_XWINDOW_H */

