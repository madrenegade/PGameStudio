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
    enum class sample_type : unsigned char
    {
        new_frame,
        allocation
    };

    class sample
    {
    public:
        sample();
        sample(const StackTrace& stacktrace, size_t bytes, size_t poolID);

        sample_type getType() const;
        
        const StackTrace& getStackTrace() const;
        
        size_t getAllocatedBytes() const;
        size_t getPoolID() const;

    private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive & ar, const unsigned int /*version*/)
        {
            ar & type;
            ar & stacktrace;
            ar & allocatedBytes;
            ar & poolID;
        }
        
        sample_type type;
        
        StackTrace stacktrace;
        size_t allocatedBytes;
        size_t poolID;
    };
}

#endif	/* MEMPROF_SAMPLE_H */

