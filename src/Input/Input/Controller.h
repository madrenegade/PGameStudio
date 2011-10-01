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
        void registerOneAxisControl(const unsigned int controlID,
                                    const char* const var,
                                    const char* const deltaVar);

        void registerTwoAxisControl(const unsigned int controlID,
                                    const char* const xVar, const char* const yVar,
                                    const char* const xDeltaVar, const char* const yDeltaVar);

        Button* getButtonFor(const unsigned int keysym);
        OneAxisControl* getOneAxisControl(const unsigned int id);
        TwoAxisControl* getTwoAxisControl(const unsigned int id);

    private:
        const String id;

        typedef std::shared_ptr<Button> ButtonPtr;
        typedef std::shared_ptr<OneAxisControl> OneAxisControlPtr;
        typedef std::shared_ptr<TwoAxisControl> TwoAxisControlPtr;

        typedef std::pair<const unsigned int, ButtonPtr> ButtonMapEntry;
        typedef std::pair<const unsigned int, OneAxisControlPtr> OneAxisControlMapEntry;
        typedef std::pair<const unsigned int, TwoAxisControlPtr> TwoAxisControlMapEntry;

        typedef Utilities::Memory::STLAllocator<ButtonMapEntry> ButtonMapAllocator;
        typedef Utilities::Memory::STLAllocator<OneAxisControlMapEntry> OneAxisControlMapAllocator;
        typedef Utilities::Memory::STLAllocator<TwoAxisControlMapEntry> TwoAxisControlMapAllocator;

        typedef std::map<unsigned int, ButtonPtr, std::less<unsigned int>, ButtonMapAllocator> ButtonMap;
        typedef std::map<unsigned int, OneAxisControlPtr, std::less<unsigned int>, OneAxisControlMapAllocator> OneAxisControlMap;
        typedef std::map<unsigned int, TwoAxisControlPtr, std::less<unsigned int>, TwoAxisControlMapAllocator> TwoAxisControlMap;

        ButtonMap buttons;
        OneAxisControlMap oneAxisControls;
        TwoAxisControlMap twoAxisControls;
    };
}

#endif	/* INPUT_CONTROLLER_H */

