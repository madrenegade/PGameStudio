/*
 * File:   X11Window.cpp
 * Author: madrenegade
 *
 * Created on November 29, 2010, 4:36 PM
 */

#include <X11/Xlib.h>
#include <stdexcept>

#include "Platform/Linux/XWindow.h"
#include "Graphics/GraphicsContext.h"
#include "Platform/Linux/GLXGraphicsContext.h"

namespace Platform
{
    namespace Linux
    {

        XWindow::XWindow(const std::shared_ptr<Utilities::Memory::MemoryManager>&, unsigned int w, unsigned int h,
                         unsigned int, bool fullscreen)
            : fbConfig(0), window(0)
        {
            openDisplay();
            findFrameBufferConfiguration();
            createWindow(w, h, fullscreen);
        }

        XWindow::~XWindow()
        {
            this->m_pGraphicsContext.reset();

            XDestroyWindow(display, window);
            XFreeColormap(display, cmap);
            XCloseDisplay(display);
        }

        void XWindow::openDisplay()
        {
            display = XOpenDisplay(0);

            if (!display)
            {
                throw std::runtime_error("Could not open X display");
            }
        }

        void XWindow::findFrameBufferConfiguration()
        {
            // Get a matching FB config
            static int visual_attribs[] = {
                GLX_X_RENDERABLE, True,
                GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
                GLX_RENDER_TYPE, GLX_RGBA_BIT,
                GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
                GLX_RED_SIZE, 8,
                GLX_GREEN_SIZE, 8,
                GLX_BLUE_SIZE, 8,
                GLX_ALPHA_SIZE, 8,
                GLX_DEPTH_SIZE, 24,
                GLX_STENCIL_SIZE, 8,
                GLX_DOUBLEBUFFER, True,
                //GLX_SAMPLE_BUFFERS  , 1,
                //GLX_SAMPLES         , 4,
                None
            };

            int glx_major;
            int glx_minor;

            // FBConfigs were added in GLX version 1.3.
            if (!glXQueryVersion(display, &glx_major, &glx_minor) ||
                    ((glx_major == 1) && (glx_minor < 3)) || (glx_major < 1))
            {
                throw std::runtime_error("Invalid GLX version");
            }

            int fbcount;
            GLXFBConfig* fbc = glXChooseFBConfig(display, DefaultScreen(display),
                                                 visual_attribs, &fbcount);
            if (!fbc)
            {
                throw std::runtime_error("Could not retreive framebuffer config");
            }

            // Pick the FB config/visual with the most samples per pixel
            int best_fbc = -1;
            int worst_fbc = -1;
            int best_num_samp = -1;
            int worst_num_samp = 999;

            for (int i = 0; i < fbcount; ++i)
            {
                XVisualInfo* vi = glXGetVisualFromFBConfig(display, fbc[i]);

                if (vi)
                {
                    int samp_buf;
                    int samples;
                    glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
                    glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLES, &samples);

                    if (best_fbc < 0 || (samp_buf && samples > best_num_samp))
                    {
                        best_fbc = i, best_num_samp = samples;
                    }

                    if (worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
                    {
                        worst_fbc = i, worst_num_samp = samples;
                    }
                }

                XFree(vi);
            }

            fbConfig = fbc[ best_fbc ];

            // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
            XFree(fbc);
        }

        void XWindow::createWindow(unsigned int width, unsigned int height, bool fullscreen)
        {
            // Get a visual
            XVisualInfo* vi = glXGetVisualFromFBConfig(display, fbConfig);

            XSetWindowAttributes windowAttributes;
            windowAttributes.colormap = cmap = XCreateColormap(display,
                                               RootWindow(display, vi->screen),
                                               vi->visual, AllocNone);

            windowAttributes.background_pixmap = None;
            windowAttributes.border_pixel = 0;
            windowAttributes.event_mask =
                ExposureMask | StructureNotifyMask |
                KeyPressMask | KeyReleaseMask |
                ButtonPressMask | ButtonReleaseMask | PointerMotionMask |
                EnterWindowMask | LeaveWindowMask |
                VisibilityChangeMask | FocusChangeMask | ResizeRedirectMask;

            if (fullscreen)
            {
                throw std::runtime_error("Fullscreen not yet supported");
            }
            else
            {
                window = XCreateWindow(display, RootWindow(display, vi->screen),
                                       0, 0, width, height, 0, vi->depth, InputOutput,
                                       vi->visual,
                                       CWBorderPixel | CWColormap | CWEventMask, &windowAttributes);

                Atom wmDelete = XInternAtom(display, "WM_DELETE_WINDOW", true);
                XSetWMProtocols(display, window, &wmDelete, 1);
            }

            if (!window)
            {
                throw std::runtime_error("Could not create window");
            }

            // Done with the visual info data
            XFree(vi);

            XStoreName(display, window, "Window");

            XMapWindow(display, window);

            m_pGraphicsContext.reset(GLXGraphicsContext::Create(display, window, fbConfig));
        }

        Graphics::GraphicsContext* XWindow::getGraphicsContext() const
        {
            return m_pGraphicsContext.get();
        }

        Display* XWindow::getDisplay() const
        {
            return display;
        }

        ::Window XWindow::getHandle() const
        {
            return window;
        }
    }
}
