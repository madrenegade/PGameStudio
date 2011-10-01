/*
 * File:   SystemScene.h
 * Author: madrenegade
 *
 * Created on September 23, 2011, 8:08 AM
 */

#ifndef INPUT_SYSTEMSCENE_H
#define	INPUT_SYSTEMSCENE_H

#include "Core/Scene/SystemScene.h"
#include "Core/Events/typedefs.h"

#include "Utilities/string.h"
#include "Utilities/IO/XmlReader.h"

namespace Input
{
    class Controller;
    class Button;
    class OneAxisControl;
    class TwoAxisControl;

    class SystemScene : public Core::SystemScene
    {
    public:
        SystemScene();
        virtual ~SystemScene();

        virtual void addOptionsTo(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties) const;

        virtual const char* getSceneFileExtension() const;

        virtual void initialize();

        virtual void load(const Utilities::IO::File::Handle& file);

        virtual tbb::task* getTask(tbb::task* parent);

    private:
        void processKeyboardControls(Controller* controller, Utilities::IO::XmlReader::Node* firstKeyNode);
        void processMouseButtonControls(Controller* controller, Utilities::IO::XmlReader::Node* firstButtonNode);
        void processMouseAxisControl(Controller* controller, Utilities::IO::XmlReader::Node* mouseAxisNode);

        void processButtonControl(Controller* controller, unsigned int button, Utilities::IO::XmlReader::Node* buttonNode);
        void processOneAxisControl(Controller* controller, unsigned int axisControl, Utilities::IO::XmlReader::Node* axisControlNode);
        void processTwoAxisControl(Controller* controller, unsigned int axisControl, Utilities::IO::XmlReader::Node* axisControlNode);

        void onButtonPressed(const Core::Events::EventID& event, const boost::any& data);
        void onButtonReleased(const Core::Events::EventID& event, const boost::any& data);
        void onMouseMoved(const Core::Events::EventID& event, const boost::any& data);

        void onCenterOnAxis(const Core::Events::EventID& event, const boost::any& data);
        void onCenterOnAxes(const Core::Events::EventID& event, const boost::any& data);

        void updateButton(unsigned int keysym, bool state);
        void updateOneAxisControl(unsigned int controlID, double x);
        void updateTwoAxisControl(unsigned int controlID, double x, double y);

        static const std::string EXTENSION;

        const unsigned int MOUSE;

        unsigned int screenWidth;
        unsigned int screenHeight;

        Core::Events::EventID setScriptVar;

        Core::Events::EventID quit;

        Core::Events::EventID keyPressed;
        Core::Events::EventID keyReleased;
        Core::Events::EventID mouseButtonPressed;
        Core::Events::EventID mouseButtonReleased;
        Core::Events::EventID mouseMoved;

        Core::Events::EventID centerOnAxis;
        Core::Events::EventID centerOnAxes;
        Core::Events::EventID centerMouse;

        typedef boost::shared_ptr<Controller> ControllerPtr;

        typedef std::pair<const String, ControllerPtr> ControllerMapEntry;
        typedef std::pair<const unsigned int, Controller*> ControlIDMapEntry;

        typedef Utilities::Memory::STLAllocator<ControllerMapEntry> ControllerMapAllocator;
        typedef Utilities::Memory::STLAllocator<ControlIDMapEntry> ControlIDMapAllocator;

        typedef std::map<String, ControllerPtr, std::less<String>, ControllerMapAllocator> ControllerMap;
        typedef std::map<unsigned int, Controller*, std::less<unsigned int>, ControlIDMapAllocator> ControlIDMap;

        ControllerMap controllers;

        ControlIDMap keysymControllerMapping;
        ControlIDMap idOneAxisControlMapping;
        ControlIDMap idTwoAxisControlMapping;

        std::vector<Button*, Utilities::Memory::STLAllocator<Button*>> dirtyButtons;
        std::vector<OneAxisControl*, Utilities::Memory::STLAllocator<OneAxisControl*>> dirtyOneAxisControls;
        std::vector<TwoAxisControl*, Utilities::Memory::STLAllocator<TwoAxisControl*>> dirtyTwoAxisControls;
    };
}

#endif	/* INPUT_SYSTEMSCENE_H */

