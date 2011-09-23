/* 
 * File:   SystemScene.h
 * Author: madrenegade
 *
 * Created on September 23, 2011, 8:08 AM
 */

#ifndef INPUT_SYSTEMSCENE_H
#define	INPUT_SYSTEMSCENE_H

#include "Core/Scene/SystemScene.h"

namespace Input
{

    class SystemScene : public Core::SystemScene
    {
    public:
        SystemScene();
        virtual ~SystemScene();
        
        virtual void addOptionsTo(const boost::shared_ptr<Utilities::Properties::PropertyManager>& properties);
        
        virtual const char* getSceneFileExtension() const;
        
        virtual void load(const Utilities::IO::File& file);
        
        virtual void initialize();
        
        virtual tbb::task* getTask(tbb::task* parent);
        
    private:
        static const std::string EXTENSION;
    };
}

#endif	/* INPUT_SYSTEMSCENE_H */

