/* 
 * File:   X11EventHandler.cpp
 * Author: madrenegade
 * 
 * Created on November 29, 2010, 6:24 PM
 */

#include "Platform/Linux/X11EventHandler.h"
#include "Core/Events/EventManager.h"

#include <glog/logging.h>

namespace Platform
{
    namespace Linux
    {

        X11EventHandler::X11EventHandler(const boost::shared_ptr<Core::Events::EventManager>& eventManager, Display* display)
        : eventManager(eventManager), display(display)
        {
            quitEvent = eventManager->getEventID("QUIT");
            keyPressEvent = eventManager->getEventID("KEY_PRESSED");
            keyReleaseEvent = eventManager->getEventID("KEY_RELEASED");
            buttonPressEvent = eventManager->getEventID("BUTTON_PRESSED");
            buttonReleaseEvent = eventManager->getEventID("BUTTON_RELEASED");
        }

        X11EventHandler::~X11EventHandler()
        {
        }

        unsigned int X11EventHandler::GetKeysym(const char* const name) const
        {
            unsigned int keysym = XStringToKeysym(name);

            if (keysym == NoSymbol)
            {
                LOG(FATAL) << "Unknown key name: " << name;
                throw std::runtime_error("Unknown key name");
            }

            return keysym;
        }

        void X11EventHandler::handleEvents()
        {
            XEvent event;

            while (XPending(display) > 0)
            {
                XNextEvent(display, &event);

                switch (event.type)
                {
                    case KeyPress:
                    {
                        auto ks = XLookupKeysym(&event.xkey, event.xkey.state);
                        LOG(INFO) << ks << ": " << XKeysymToString(ks);
                        eventManager->pushEvent(keyPressEvent, static_cast<unsigned int> (ks));
                    }
                        break;

                    case KeyRelease:
                        eventManager->pushEvent(keyReleaseEvent, static_cast<unsigned int> (XLookupKeysym(&event.xkey, event.xkey.state)));
                        break;

                    case ButtonPress:
                        eventManager->pushEvent(buttonPressEvent, std::make_tuple(event.xbutton.button,
                            event.xbutton.x, event.xbutton.y));
                        break;

                    case ButtonRelease:
                        eventManager->pushEvent(buttonReleaseEvent, std::make_tuple(event.xbutton.button,
                            event.xbutton.x, event.xbutton.y));
                        break;

                    case MotionNotify:
                        //                       eventManager->pushEvent(this->m_mouseMotionEvent,
                        //                            Core::MouseMotionEvent(event.xmotion.x,
                        //                            event.xmotion.y));
                        break;

                    case EnterNotify:
                        //                        this->m_pEventHandler->PushEvent(this->m_activeEvent, true);
                        break;

                    case LeaveNotify:
                        //                        this->m_pEventHandler->PushEvent(this->m_activeEvent, false);
                        break;

                    case FocusIn:
                        //                        this->m_pEventHandler->PushEvent(this->m_minimizeEvent, false);
                        break;

                    case FocusOut:
                        //                        this->m_pEventHandler->PushEvent(this->m_minimizeEvent, true);
                        break;

                    case Expose:
                        //                        Logger::Warning("Unhandled event: Expose");
                        break;

                    case GraphicsExpose:
                        //                        Logger::Warning("Unhandled event: GraphicsExpose");
                        break;

                    case NoExpose:
                        //                        Logger::Warning("Unhandled event: NoExpose");
                        break;

                    case VisibilityNotify:
                        //                        Logger::Warning("Unhandled event: Visibility");
                        break;

                    case CreateNotify:
                        //                        Logger::Warning("Unhandled event: Create");
                        break;

                    case DestroyNotify:
                        //                        Logger::Warning("Unhandled event: Destroy");
                        break;

                    case ConfigureNotify:
                        //                        Logger::Warning("Unhandled event: Configure");
                        break;

                    case ConfigureRequest:
                        //                        Logger::Warning("Unhandled event: ConfigureRequest");
                        break;

                    case ResizeRequest:
                        //                        this->m_pEventHandler->PushEvent(this->m_resizeEvent,
                        //                                                         Core::ResizeEvent(event.xresizerequest.width,
                        //                                                                           event.xresizerequest.height));
                        break;

                    case ClientMessage:
                        eventManager->pushEvent(quitEvent, 0);
                        return;

                    default:
                        //                        Logger::Warning("Unhandled unknown event");
                        break;
                }
            }
        }
    }
}


