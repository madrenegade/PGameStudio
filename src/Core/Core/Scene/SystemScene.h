/* 
 * File:   SystemScene.h
 * Author: madrenegade
 *
 * Created on September 16, 2011, 2:28 PM
 */

#ifndef CORE_SYSTEMSCENE_H
#define	CORE_SYSTEMSCENE_H

#include <tbb/task.h>
#include <boost/shared_ptr.hpp>

namespace Utilities
{
    namespace Memory
    {
        class MemoryManager;
    }
    
    namespace IO
    {
        class File;
    }
}

namespace Platform
{
    class PlatformManager;
}

namespace Core
{
    namespace Events
    {
        class EventManager;
    }
    
    class SystemScene
    {
    public:
        virtual ~SystemScene();
        
        virtual const char* getSceneFileExtension() const = 0;
        
        virtual void load(const Utilities::IO::File& file) = 0;
        
        virtual void initialize();

        /**
         * Set the memory manager which should be used by this system scene.
         * @param memoryManager - the memory manager to use
         */
        void setMemoryManager(const boost::shared_ptr<Utilities::Memory::MemoryManager>& memoryManager);
        
        /**
         * Make the platform manager available to this system scene.
         * @param platformManager
         */
        void setPlatformManager(const boost::shared_ptr<Platform::PlatformManager>& platformManager);
        
        void setEventManager(const boost::shared_ptr<Events::EventManager>& eventManager);

        virtual tbb::task* getTask(tbb::task* parent) = 0;

    protected:
        SystemScene();

        boost::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        boost::shared_ptr<Platform::PlatformManager> platformManager;
        boost::shared_ptr<Events::EventManager> eventManager;
    };
}

#endif	/* CORE_SYSTEMSCENE_H */

