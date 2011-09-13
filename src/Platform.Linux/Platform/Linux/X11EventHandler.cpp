/* 
 * File:   X11EventHandler.cpp
 * Author: madrenegade
 * 
 * Created on November 29, 2010, 6:24 PM
 */

#include "Platform/Linux/X11EventHandler.h"
#include "Core/Events/EventManager.h"

namespace Platform
{
    namespace Linux
    {

        X11EventHandler::X11EventHandler(const boost::shared_ptr<Core::Events::EventManager>& eventManager, Display* display)
        : eventManager(eventManager), display(display)
        {
            quitEvent = eventManager->getEventID("QUIT");
        }

        X11EventHandler::~X11EventHandler()
        {
        }

//        unsigned int X11EventHandler::GetKeysym(const char* const name) const
//        {
//            unsigned int keysym = XStringToKeysym(name);
//
//            if(keysym == NoSymbol)
//            {
//                throw std::runtime_error("Unknown key name");
//            }
//
//            return keysym;
//        }

        void X11EventHandler::handleEvents()
        {
            XEvent event;

            while(XPending(display) > 0)
            {
                XNextEvent(display, &event);

                switch(event.type)
                {
                    case KeyPress:
//                        Logger::Debug(XKeysymToString(XLookupKeysym(&event.xkey, 0)));
//                        eventHandler->pushEvent(this->m_keyPressEvent, static_cast<unsigned int> (XLookupKeysym(&event.xkey, 0)));
                        break;

                    case KeyRelease:
//                        this->m_pEventHandler->PushEvent(this->m_keyReleaseEvent, static_cast<unsigned int> (XLookupKeysym(&event.xkey, 0)));
                        break;

                    case ButtonPress:
//                        this->m_pEventHandler->PushEvent(this->m_mousePressEvent,
//                                                         Core::MouseButtonEvent(event.xbutton.button,
//                                                                                event.xbutton.x,
//                                                                                event.xbutton.y));
                        break;

                    case ButtonRelease:
//                        this->m_pEventHandler->PushEvent(this->m_mouseReleaseEvent,
//                                                         Core::MouseButtonEvent(event.xbutton.button,
//                                                                                event.xbutton.x,
//                                                                                event.xbutton.y));
                        break;

                    case MotionNotify:
//                        this->m_pEventHandler->PushEvent(this->m_mouseMotionEvent,
//                                                         Core::MouseMotionEvent(event.xmotion.x,
//                                                                                event.xmotion.y));
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


