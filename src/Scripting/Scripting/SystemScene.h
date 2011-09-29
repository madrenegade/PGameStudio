/* 
 * File:   SystemScene.h
 * Author: madrenegade
 *
 * Created on September 27, 2011, 2:00 PM
 */

#ifndef SCRIPTING_SYSTEMSCENE_H
#define	SCRIPTING_SYSTEMSCENE_H

#include "Core/Scene/SystemScene.h"

namespace Scripting
{
    class ScriptManager;
    
    class SystemScene : public Core::SystemScene
    {
    public:
        SystemScene();
        virtual ~SystemScene();

        virtual void addOptionsTo(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties) const;

        virtual const char* getSceneFileExtension() const;

        virtual void load(const Utilities::IO::File& file);

        virtual void initialize();

        virtual tbb::task* getTask(tbb::task* parent);
        
    private:
        static const std::string EXTENSION;
        
        ScriptManager* scriptManager;
    };
}

#endif	/* SCRIPTING_SYSTEMSCENE_H */

