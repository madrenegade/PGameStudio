/*
 * File:   Window.h
 * Author: madrenegade
 *
 * Created on September 13, 2011, 3:37 PM
 */

#ifndef GRAPHICS_WINDOW_H
#define GRAPHICS_WINDOW_H

#include <memory>

namespace Utilities
{
    namespace Properties
    {
        class PropertyManager;
    }
}

namespace Graphics
{
    class GraphicsContext;

    class Window
    {
    public:
        static void addOptionsTo(Utilities::Properties::PropertyManager* const properties);

        virtual ~Window();

        /**
         * NOTE: The window has to take the ownership of the context pointer.
         * @return the graphics context associated with this window
         */
        virtual GraphicsContext* getGraphicsContext() const = 0;

    protected:
        Window();
    };
}

#endif	/* GRAPHICS_WINDOW_H */

