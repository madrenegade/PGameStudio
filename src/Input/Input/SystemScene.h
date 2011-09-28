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

namespace Input
{
    class Controller;
    class Button;
    
    class SystemScene : public Core::SystemScene
    {
    public:
        SystemScene();
        virtual ~SystemScene();
        
        virtual void addOptionsTo(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties) const;
        
        virtual const char* const getSceneFileExtension() const;
        
        virtual void initialize();
        
        virtual void load(const Utilities::IO::File& file);
        
        virtual tbb::task* getTask(tbb::task* parent);
        
    private:
        void onKeyPressed(const Core::Events::EventID& event, const boost::any& data);
        void onKeyReleased(const Core::Events::EventID& event, const boost::any& data);
        
        void updateButton(unsigned int keysym, bool state);
        
        static const std::string EXTENSION;
        
        Core::Events::EventID setScriptVar;
        
        Core::Events::EventID quit;
        
        Core::Events::EventID keyPressed;
        Core::Events::EventID keyReleased;
        
        typedef boost::shared_ptr<Controller> ControllerPtr;
        
        typedef std::map<String, ControllerPtr> ControllerMap;
        ControllerMap controllers;
        
        typedef std::map<unsigned int, Controller*> KeysymMap;
        KeysymMap keysymControllerMapping;
        
        std::vector<Button*, Utilities::Memory::STLAllocator<Button*>> dirtyButtons;
    };
}

#endif	/* INPUT_SYSTEMSCENE_H */

