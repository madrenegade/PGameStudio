/* 
 * File:   Window.cpp
 * Author: madrenegade
 * 
 * Created on September 13, 2011, 3:37 PM
 */

#include "Graphics/Window.h"
#include "Utilities/Properties/PropertyManager.h"

using namespace Utilities::Properties;

namespace Graphics
{

    void Window::addOptionsTo(const PropertyManager::Ptr& properties)
    {
        po::options_description options("Filesystem options");

        options.add_options()
            ("Window.width", po::value<unsigned int>()->default_value(800), "The window width.")
            ("Window.height", po::value<unsigned int>()->default_value(600), "The window height.")
            ("Window.bitsPerPixel", po::value<unsigned int>()->default_value(16), "Colordepth for the window.")
            ("Window.fullscreen", po::value<bool>()->default_value(false), "Flag indicating wether to start in fullscreen or windowed mode")
            ("Graphics.renderer", po::value<std::string > ()->default_value("NULL"), "The renderer backend to use");

        properties->addOptions(options);
    }

    Window::Window()
    {
    }

    Window::~Window()
    {
    }
}
