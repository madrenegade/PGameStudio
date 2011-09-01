/* 
 * File:   MemoryManagerSettings.h
 * Author: madrenegade
 *
 * Created on September 1, 2011, 3:16 PM
 */

#ifndef UTILITIES_MEMORY_MEMORYMANAGERSETTINGS_H
#define	UTILITIES_MEMORY_MEMORYMANAGERSETTINGS_H

#include "Utilities/Memory/constants.h"

namespace Utilities
{
    namespace Memory
    {

        struct MemoryManagerSettings
        {

            MemoryManagerSettings(size_t threshold = 64 * Byte,
                                  size_t maxMemoryForSmallObjects = 1 * MByte,
                                  size_t smallObjectDefaultPageSize = 4 * KByte,
                                  size_t maxMemoryForLargeObjects = 4 * MByte,
                                  size_t largeObjectDefaultPageSize = 4 * KByte)
            : threshold(threshold),
            maxMemoryForSmallObjects(maxMemoryForSmallObjects), smallObjectDefaultPageSize(smallObjectDefaultPageSize),
            maxMemoryForLargeObjects(maxMemoryForLargeObjects), largeObjectDefaultPageSize(largeObjectDefaultPageSize)
            {
            }

            /**
             * value in bytes to indicate the threshold between when 
             * the manager for small objects or large objects should be used
             */
            size_t threshold;

            size_t maxMemoryForSmallObjects;
            size_t smallObjectDefaultPageSize;

            size_t maxMemoryForLargeObjects;
            size_t largeObjectDefaultPageSize;
        };
    }
}

#endif	/* UTILITIES_MEMORY_MEMORYMANAGERSETTINGS_H */

