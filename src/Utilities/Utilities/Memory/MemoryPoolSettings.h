/*
 * File:   MemoryPoolSettings.h
 * Author: madrenegade
 *
 * Created on September 2, 2011, 10:30 PM
 */

#ifndef UTILITIES_MEMORY_MEMORYPOOLSETTINGS_H
#define	UTILITIES_MEMORY_MEMORYPOOLSETTINGS_H

#include "Utilities/Memory/constants.h"


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
            void addOptionsTo(Properties::PropertyManager* const properties, const char* const basename) const;

            /**
             * Load memory pool settings from a property manager
             * @param properties
             * @param basename
             * @return the loaded settings
             */
            static const MemoryPoolSettings loadFrom(const Properties::PropertyManager* const properties,
                                                     const char* const basename);

            MemoryPoolSettings(const size_t smallObjectPoolSize = 16*KByte,
                               const size_t smallObjectPageSize = 4*KByte,
                               const size_t smallObjectBlockSize = 128*Byte,
                               const size_t mediumObjectPoolSize = 4*MByte,
                               const size_t mediumObjectPageSize = 4*KByte,
                               const size_t mediumObjectBlockSize = 128*Byte,
                               const size_t largeObjectPoolSize = 16*MByte,
                               const size_t largeObjectPageSize = 4*KByte,
                               const size_t largeObjectBlockSize = 512*Byte);

            const size_t smallObjectPoolSize;
            const size_t smallObjectPageSize;
            const size_t smallObjectBlockSize;
            const size_t mediumObjectPoolSize;
            const size_t mediumObjectPageSize;
            const size_t mediumObjectBlockSize;
            const size_t largeObjectPoolSize;
            const size_t largeObjectPageSize;
            const size_t largeObjectBlockSize;
        };


    }
}

#endif	/* UTILITIES_MEMORY_MEMORYPOOLSETTINGS_H */

