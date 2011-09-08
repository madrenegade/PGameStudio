#include "samplenode.h"
#include <iostream>

SampleNode::SampleNode()
{

}

SampleNode::SampleNode(const std::string& name)
    : name(name), numAllocations(0), allocationSize(0), numAllocationsPerFrame(0.0),
      allocationSizePerFrame(0.0),
      currentFrame(0),
      numAllocationsForCurrentFrame(0), allocationSizeForCurrentFrame(0)
{
}

const std::string& SampleNode::getName() const
{
    return name;
}

const SampleNode::Children& SampleNode::getChildren() const
{
    return children;
}

size_t SampleNode::getNumAllocations() const
{
    size_t numAllocations = getNumSelfAllocations();

    for(Children::const_iterator i = children.begin(); i != children.end(); ++i)
    {
        numAllocations += i->second.getNumAllocations();
    }

    return numAllocations;
}

size_t SampleNode::getNumSelfAllocations() const
{
    return numAllocations;
}

size_t SampleNode::getTotalSize() const
{
    size_t total = getSelfSize();

    for(Children::const_iterator i = children.begin(); i != children.end(); ++i)
    {
        total += i->second.getTotalSize();
    }

    return total;
}

size_t SampleNode::getSelfSize() const
{
    return allocationSize;
}

double SampleNode::getNumAllocationsPerFrame() const
{
    size_t total = getNumSelfAllocationsPerFrame();

    std::for_each(children.begin(), children.end(), [&total](std::pair<std::string, SampleNode> i) {
        total += i.second.getNumAllocationsPerFrame();
    });

    return total;
}

double SampleNode::getNumSelfAllocationsPerFrame() const
{
    // finished frames + current frame
    return numAllocationsPerFrame + (numAllocationsForCurrentFrame / (currentFrame+1));
}

double SampleNode::getTotalSizePerFrame() const
{
    size_t total = getSelfSizePerFrame();

    std::for_each(children.begin(), children.end(), [&total](std::pair<std::string, SampleNode> i) {
        total += i.second.getTotalSizePerFrame();
    });

    return total;
}

double SampleNode::getSelfSizePerFrame() const
{
    return allocationSizePerFrame + (allocationSizeForCurrentFrame / (currentFrame+1));
}

 void SampleNode::add(const memprof::sample& sample, size_t frame)
 {
     StackTrace stackTrace(sample.getStackTrace());
     StackFrames stackFrames(stackTrace.getFrames());

     add(stackFrames, sample.getAllocatedBytes(), frame);
 }

 void SampleNode::add(StackFrames& stackFrames, size_t bytes, size_t frame)
 {
     if(frame > currentFrame)
     {
         currentFrame = frame;

         numAllocationsPerFrame += (numAllocationsForCurrentFrame / currentFrame);
         allocationSizePerFrame += (allocationSizeForCurrentFrame / currentFrame);
         numAllocationsForCurrentFrame = 0;
         allocationSizeForCurrentFrame = 0;
     }

     StackFrame top(stackFrames.front());

     if(top.getFunction() == name)
     {
         std::cout << name << std::endl;

         stackFrames.pop_front();

         if(stackFrames.empty())
         {
             addAllocation(bytes);
             return;
         }

         StackFrame firstChild(stackFrames.front());

         std::string function(firstChild.getFunction());

         if(children.find(function) == children.end())
         {
             children[function] = SampleNode(function);
         }

         SampleNode& childNode = children[function];
         childNode.add(stackFrames, bytes, frame);
     }
     else
     {
         throw std::runtime_error("Invalid data");
     }

 }

void SampleNode::addAllocation(size_t bytes)
{
    ++numAllocations;
    ++numAllocationsForCurrentFrame;
    allocationSize += bytes;
    allocationSizeForCurrentFrame += bytes;
}
