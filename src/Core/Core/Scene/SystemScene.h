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
}

namespace Platform
{
    class PlatformManager;
}

namespace Core
{

    class SystemScene
    {
    public:
        virtual ~SystemScene();

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

        virtual tbb::task* getTask(tbb::task* parent) = 0;

    protected:
        SystemScene();

        boost::shared_ptr<Utilities::Memory::MemoryManager> memoryManager;
        boost::shared_ptr<Platform::PlatformManager> platformManager;
    };
}

#endif	/* CORE_SYSTEMSCENE_H */

