/* 
 * File:   MemoryPoolSettings.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 10:30 PM
 */

#ifndef UTILITIES_MEMORY_MEMORYPOOLSETTINGS_H
#define	UTILITIES_MEMORY_MEMORYPOOLSETTINGS_H

#include "Utilities/Memory/constants.h"
#include <boost/shared_ptr.hpp>

namespace Utilities
{
    namespace Properties
    {
        class PropertyManager;
    }
    
    namespace Memory
    {

        struct MemoryPoolSettings
        {
            /**
             * Add options to the properties using a basename for determining the property name.
             * The settings from this object are used as default property values.
             * @param properties - the property manager to add the options to
             * @param basename - the basename used for the property names
             */
            void addOptionsTo(const boost::shared_ptr<Properties::PropertyManager>& properties, const char* basename);
            
            /**
             * Load memory pool settings from a property manager
             * @param properties
             * @param basename
             * @return the loaded settings
             */
            static MemoryPoolSettings loadFrom(const boost::shared_ptr<Properties::PropertyManager>& properties, const char* basename);
        
            MemoryPoolSettings(size_t smallObjectPoolSize = 16*KByte,
                               size_t smallObjectPageSize = 4*KByte,
                               size_t smallObjectBlockSize = 128*Byte,
                               size_t mediumObjectPoolSize = 4*MByte,
                               size_t mediumObjectPageSize = 4*KByte,
                               size_t mediumObjectBlockSize = 128*Byte,
                               size_t largeObjectPoolSize = 16*MByte,
                               size_t largeObjectPageSize = 4*KByte,
                               size_t largeObjectBlockSize = 512*Byte)
            : smallObjectPoolSize(smallObjectPoolSize),
            smallObjectPageSize(smallObjectPageSize),
            smallObjectBlockSize(smallObjectBlockSize),
            mediumObjectPoolSize(mediumObjectPoolSize),
            mediumObjectPageSize(mediumObjectPageSize),
            mediumObjectBlockSize(mediumObjectBlockSize),
            largeObjectPoolSize(largeObjectPoolSize),
            largeObjectPageSize(largeObjectPageSize),
            largeObjectBlockSize(largeObjectBlockSize)
            {
            }

            size_t smallObjectPoolSize;
            size_t smallObjectPageSize;
            size_t smallObjectBlockSize;
            size_t mediumObjectPoolSize;
            size_t mediumObjectPageSize;
            size_t mediumObjectBlockSize;
            size_t largeObjectPoolSize;
            size_t largeObjectPageSize;
            size_t largeObjectBlockSize;
        };
        
        
    }
}

#endif	/* UTILITIES_MEMORY_MEMORYPOOLSETTINGS_H */

