#ifndef STACKTRACE_H
#define STACKTRACE_H

#include <list>
#include "StackFrame.h"

#include <boost/serialization/list.hpp>

class StackTrace
{
public:
    StackTrace(bool x = true);
    
    const std::list<StackFrame>& getFrames() const;
    
private:
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & frames;
    }
    
    std::list<StackFrame> frames;
};

#endif // STACKTRACE_H