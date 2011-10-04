#ifndef STACKTRACE_H
#define STACKTRACE_H

#include <list>
#include "StackFrame.h"

#include <boost/serialization/list.hpp>

class StackTrace
{
public:
    typedef std::list<StackFrame> Frames;

    /**
     * Construct a StackTrace object.
     * @param createStackTrace - True if stackframes should be generated, false otherwise.
     */
    StackTrace(const bool createStackFrames = true);

    /**
     * Retreive the generated stack frames.
     * @return A collection of stack frames generated by this stack trace.
     */
    const Frames& getFrames() const;

private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& frames;
    }

    std::list<StackFrame> frames;
};

#endif // STACKTRACE_H
