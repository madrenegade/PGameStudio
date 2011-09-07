#include "samplenode.h"
#include <iostream>

SampleNode::SampleNode()
{

}

SampleNode::SampleNode(const std::string& name)
    : name(name)
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
    size_t numAllocations = allocations.size();

    for(Children::const_iterator i = children.begin(); i != children.end(); ++i)
    {
        numAllocations += i->second.getNumAllocations();
    }

    return numAllocations;
}

size_t SampleNode::getNumSelfAllocations() const
{
    return allocations.size();
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
    size_t total = 0;

    for(Allocations::const_iterator i = allocations.begin(); i != allocations.end(); ++i)
    {
        total += *i;
    }

    return total;
}

 void SampleNode::add(const memprof::sample& sample)
 {
     StackTrace stackTrace(sample.getStackTrace());

     StackFrames stackFrames(stackTrace.getFrames());

     add(stackFrames, sample.getAllocatedBytes());
 }

 void SampleNode::add(StackFrames& stackFrames, size_t bytes)
 {
     StackFrame top(stackFrames.front());

     if(top.getFunction() == name)
     {
         std::cout << name << std::endl;

         stackFrames.pop_front();

         if(stackFrames.empty())
         {
             allocations.push_front(bytes);
             std::cout << "END" << std::endl;
             return;
         }

         StackFrame firstChild(stackFrames.front());

         std::string function(firstChild.getFunction());

         std::cout << "Child: " << function << std::endl;

         if(children.find(function) == children.end())
         {
             std::cout << "NEW" << std::endl;
             children[function] = SampleNode(function);
         }
         else
         {
             std::cout << "CONTINUE" << std::endl;
         }

         SampleNode& childNode = children[function];
         childNode.add(stackFrames, bytes);
     }
     else
     {
         throw std::runtime_error("Invalid data");
     }

 }
