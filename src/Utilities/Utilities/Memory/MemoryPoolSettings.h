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
    namespace Memory
    {

        struct MemoryPoolSettings
        {
            MemoryPoolSettings(size_t smallObjectPoolSize = 128*Byte,
                               size_t smallObjectPageSize = 64*Byte,
                               size_t smallObjectBlockSize = 8*Byte,
                               size_t mediumObjectPoolSize = 1*MByte,
                               size_t mediumObjectPageSize = 4*KByte,
                               size_t mediumObjectBlockSize = 64*Byte,
                               size_t largeObjectPoolSize = 1*MByte,
                               size_t largeObjectPageSize = 4*KByte,
                               size_t largeObjectBlockSize = 128*Byte)
            : smallObjectPoolSize(smallObjectPoolSize),
            smallObjectPageSize(smallObjectPageSize),
            smallObjectBlockSize(smallObjectBlockSize),
            mediumObjectPoolSize(mediumObjectPoolSize),
            mediumObjectPageSize(mediumObjectPoolSize),
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

