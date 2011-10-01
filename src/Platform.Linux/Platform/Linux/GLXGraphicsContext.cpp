/*
 * File:   GlxGraphicsContext.cpp
 * Author: madrenegade
 *
 * Created on November 29, 2010, 4:36 PM
 */

#include "Platform/Linux/GLXGraphicsContext.h"
#include <stdexcept>
#include <cstring>
#include <GL/glx.h>

#include <glog/logging.h>

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092
typedef GLXContext(*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

namespace Platform
{
    namespace Linux
    {

        static bool isExtensionSupported(const char* extList, const char* extension)
        {

            const char* start;
            const char* where, *terminator;

            /* Extension names should not have spaces. */
            where = strchr(extension, ' ');
            if (where || *extension == '\0')
                return false;

            /* It takes a bit of care to be fool-proof about parsing the
               OpenGL extensions string. Don't be fooled by sub-strings,
               etc. */
            for (start = extList;;)
            {
                where = strstr(start, extension);

                if (!where)
                    break;

                terminator = where + strlen(extension);

                if (where == start || *(where - 1) == ' ')
                    if (*terminator == ' ' || *terminator == '\0')
                        return true;

                start = terminator;
            }

            return false;
        }

        static bool ctxErrorOccurred = false;

        static int ctxErrorHandler(Display* dpy, XErrorEvent* ev)
        {
            ctxErrorOccurred = true;
            return 0;
        }

        GLXGraphicsContext* GLXGraphicsContext::Create(Display* pDisplay,
                Window window,
                GLXFBConfig fbConfig)
        {
            return CreateInternalContext(pDisplay, window, fbConfig);
        }

        GLXGraphicsContext* GLXGraphicsContext::CreateInternalContext(Display* pDisplay, Window window, GLXFBConfig fbConfig)
        {
            // Get the default screen's GLX extension list
            const char* glxExts = glXQueryExtensionsString(pDisplay, DefaultScreen(pDisplay));

            // NOTE: It is not necessary to create or make current to a context before
            // calling glXGetProcAddressARB
            glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
            glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)
                                         glXGetProcAddressARB((const GLubyte*) "glXCreateContextAttribsARB");

            GLXContext ctx = 0;

            // Install an X error handler so the application won't exit if GL 3.0
            // context allocation fails.
            //
            // Note this error handler is global.  All display connections in all threads
            // of a process use the same error handler, so be sure to guard against other
            // threads issuing X commands while this code is running.
            ctxErrorOccurred = false;
            int (*oldHandler)(Display*, XErrorEvent*) = XSetErrorHandler(&ctxErrorHandler);

            // Check for the GLX_ARB_create_context extension string and the function.
            // If either is not present, use GLX 1.3 context creation method.
            if (!isExtensionSupported(glxExts, "GLX_ARB_create_context") ||
                    !glXCreateContextAttribsARB)
            {
                ctx = glXCreateNewContext(pDisplay, fbConfig, GLX_RGBA_TYPE, 0, True);
            }
            else
            {

                int context_attribs[] = {
                    GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                    GLX_CONTEXT_MINOR_VERSION_ARB, 0,
                    //GLX_CONTEXT_FLAGS_ARB        , GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                    None
                };

                ctx = glXCreateContextAttribsARB(pDisplay, fbConfig, 0, True, context_attribs);
            }

            // Sync to ensure any errors generated are processed.
            XSync(pDisplay, False);

            if (ctxErrorOccurred || !ctx)
            {
                throw std::runtime_error("OpenGL 3.0 not supported");
            }

            // Sync to ensure any errors generated are processed.
            XSync(pDisplay, False);

            // Restore the original error handler
            XSetErrorHandler(oldHandler);

            if (ctxErrorOccurred || !ctx)
            {
                throw std::runtime_error("Could not create context");
            }

            // Verifying that context is a direct context
            if (!glXIsDirect(pDisplay, ctx))
            {
                throw std::runtime_error("Direct rendering not supported");
            }

            return new GLXGraphicsContext(pDisplay, window, ctx);
        }

        GLXGraphicsContext::GLXGraphicsContext(Display* pDisplay,
                                               Window window,
                                               GLXContext context)
            : m_pDisplay(pDisplay), m_windowHandle(window), m_context(context)
        {
        }

        GLXGraphicsContext::~GLXGraphicsContext()
        {
            if (this->m_context)
            {
                glXDestroyContext(this->m_pDisplay, this->m_context);
            }
        }

        void GLXGraphicsContext::MakeCurrent()
        {
            if (!glXMakeCurrent(this->m_pDisplay, this->m_windowHandle, this->m_context))
            {
                throw std::runtime_error("MakeCurrent failed");
            }
        }

        void GLXGraphicsContext::Release()
        {
            if (!glXMakeCurrent(this->m_pDisplay, None, 0))
            {
                throw std::runtime_error("Cannot release glx context");
            }
        }

        void GLXGraphicsContext::SwapBuffers()
        {
            glXSwapBuffers(this->m_pDisplay, this->m_windowHandle);
        }
    }
}


