/*
 * File:   StackFrame.cpp
 * Author: madrenegade
 *
 * Created on September 7, 2011, 9:40 AM
 */

#include "StackFrame.h"

StackFrame::StackFrame()
{

}

StackFrame::StackFrame(const std::string& function)
    : function(function)
{

}

const std::string& StackFrame::getFunction() const
{
    return function;
}
