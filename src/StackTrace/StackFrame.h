/* 
 * File:   StackFrame.h
 * Author: madrenegade
 *
 * Created on September 7, 2011, 9:40 AM
 */

#ifndef STACKFRAME_H
#define	STACKFRAME_H

#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class StackFrame
{
public:
    StackFrame();
    StackFrame(const std::string& function);
    
    const std::string& getFunction() const;
    
private:
    friend class boost::serialization::access;
    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & function;
    }
    
    std::string function;
};

#endif	/* STACKFRAME_H */

