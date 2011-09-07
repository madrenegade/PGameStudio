#ifndef SAMPLENODE_H
#define SAMPLENODE_H

#include "memprof/sample.h"

#include <map>

class SampleNode
{
public:
    typedef std::map<std::string, SampleNode> Children;
    typedef std::list<size_t> Allocations;

    SampleNode();
    SampleNode(const std::string& name);

    void add(const memprof::sample& sample);

    const std::string& getName() const;

    const Children& getChildren() const;

    size_t getNumAllocations() const;
    size_t getNumSelfAllocations() const;
    size_t getTotalSize() const;
    size_t getSelfSize() const;

private:
    typedef std::list<StackFrame> StackFrames;

    void add(StackFrames& stackFrames, size_t size);

    std::string name;

    Children children;

    Allocations allocations;
};

#endif // SAMPLENODE_H
