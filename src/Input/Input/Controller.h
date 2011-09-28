/* 
 * File:   Controller.h
 * Author: madrenegade
 *
 * Created on September 28, 2011, 11:39 AM
 */

#ifndef INPUT_CONTROLLER_H
#define	INPUT_CONTROLLER_H

#include "Utilities/string.h"
#include "Input/Button.h"

namespace Input
{
    class Controller
    {
    public:
        Controller(const String& id);
        ~Controller();
        
        const String& getID() const;
        
        void registerButton(const unsigned int keysym, const Core::Events::EventID& event);
        
        Button* getButtonFor(const unsigned int keysym);
        
    private:
        const String id;
        
        typedef std::shared_ptr<Button> ButtonPtr;
        
        typedef std::map<unsigned int, ButtonPtr> ButtonMap;
        ButtonMap buttons;
    };
}

#endif	/* INPUT_CONTROLLER_H */

