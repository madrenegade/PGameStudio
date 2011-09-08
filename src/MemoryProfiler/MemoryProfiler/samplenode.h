#ifndef SAMPLENODE_H
#define SAMPLENODE_H

#include "memprof/sample.h"

#include <map>

class SampleNode
{
public:
    typedef std::map<std::string, SampleNode> Children;

    SampleNode();
    SampleNode(const std::string& name);

    void add(const memprof::sample& sample, size_t frame);

    const std::string& getName() const;

    const Children& getChildren() const;

    size_t getNumAllocations() const;
    size_t getNumSelfAllocations() const;
    size_t getTotalSize() const;
    size_t getSelfSize() const;

    double getNumAllocationsPerFrame() const;
    double getNumSelfAllocationsPerFrame() const;

    double getTotalSizePerFrame() const;
    double getSelfSizePerFrame() const;

private:
    typedef std::list<StackFrame> StackFrames;

    void add(StackFrames& stackFrames, size_t size, size_t frame);

    void addAllocation(size_t bytes);

    std::string name;

    Children children;

    size_t numAllocations;
    size_t allocationSize;

    static size_t getCurrentFrame();
    static size_t currentFrame;
};

#endif // SAMPLENODE_H
