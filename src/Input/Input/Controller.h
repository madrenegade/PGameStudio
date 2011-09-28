/* 
 * File:   Controller.h
 * Author: madrenegade
 *
 * Created on September 28, 2011, 11:39 AM
 */

#ifndef INPUT_CONTROLLER_H
#define	INPUT_CONTROLLER_H

#include "Utilities/string.h"

namespace Input
{
    class Button;
    class OneAxisControl;
    class TwoAxisControl;
    
    class Controller
    {
    public:
        Controller(const String& id);
        ~Controller();
        
        const String& getID() const;
        
        void registerButton(const unsigned int keysym, const char* const var);
        void registerOneAxisControl(const unsigned int controlID, const char* const var);
        void registerTwoAxisControl(const unsigned int controlID, const char* const xVar, const char* const yVar);
        
        Button* getButtonFor(const unsigned int keysym);
        OneAxisControl* getOneAxisControl(const unsigned int id);
        TwoAxisControl* getTwoAxisControl(const unsigned int id);
        
    private:
        const String id;
        
        typedef std::shared_ptr<Button> ButtonPtr;
        typedef std::shared_ptr<OneAxisControl> OneAxisControlPtr;
        typedef std::shared_ptr<TwoAxisControl> TwoAxisControlPtr;
        
        typedef std::map<unsigned int, ButtonPtr> ButtonMap;
        typedef std::map<unsigned int, OneAxisControlPtr> OneAxisControlMap;
        typedef std::map<unsigned int, TwoAxisControlPtr> TwoAxisControlMap;
        
        ButtonMap buttons;
        OneAxisControlMap oneAxisControls;
        TwoAxisControlMap twoAxisControls;
    };
}

#endif	/* INPUT_CONTROLLER_H */

