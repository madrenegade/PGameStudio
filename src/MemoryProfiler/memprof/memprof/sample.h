/* 
 * File:   sample.h
 * Author: madrenegade
 *
 * Created on September 7, 2011, 11:58 AM
 */

#ifndef MEMPROF_SAMPLE_H
#define	MEMPROF_SAMPLE_H

#include <boost/serialization/access.hpp>
#include "StackTrace.h"

namespace memprof
{

    class sample
    {
    public:
        sample();
        sample(const StackTrace& stacktrace, size_t bytes);

        const StackTrace& getStackTrace() const;
        size_t getAllocatedBytes() const;

    private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & stacktrace;
            ar & allocatedBytes;
        }
        
        StackTrace stacktrace;
        size_t allocatedBytes;
    };
}

#endif	/* MEMPROF_SAMPLE_H */

