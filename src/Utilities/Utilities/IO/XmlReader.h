/* 
 * File:   XmlReader.h
 * Author: madrenegade
 *
 * Created on September 22, 2011, 7:54 PM
 */

#ifndef UTILITIES_IO_XMLREADER_H
#define	UTILITIES_IO_XMLREADER_H

typedef struct _xmlDoc xmlDoc;
typedef struct _xmlXPathContext xmlXPathContext;

#include <boost/shared_ptr.hpp>
#include <sstream>

#include "Utilities/string.h"

namespace Utilities
{
    namespace IO
    {
        class File;
        
        class XmlReader
        {
        public:
            XmlReader(const boost::shared_ptr<Memory::MemoryManager>& memory, const File& file);
            ~XmlReader();
            
            template<typename ContainerType>
            void getAttributeValues(const char* const xpath, ContainerType& container) const
            {
                std::vector<String, Utilities::Memory::STLAllocator<String>> results;
                evaluate(reinterpret_cast<const unsigned char*>(xpath), results);
                
                std::stringstream stream;
                
                std::for_each(results.begin(), results.end(), [&stream, &container](const String& s){
                    typename ContainerType::value_type obj;
                    LOG(INFO) << "IN: " << s;
                    stream << s;
                    stream >> obj;
                    LOG(INFO) << "OUT: " << obj;
                    stream.clear();
                    
                    container.push_back(obj);
                });
            }
            
        private:
            void evaluate(const unsigned char* xpath,
                          std::vector<String, Utilities::Memory::STLAllocator<String>>& results) const;
            
            std::shared_ptr<xmlDoc> doc;
            std::shared_ptr<xmlXPathContext> context;
            
            static Memory::MemoryManager* memory;
            static void deallocate(void* ptr);
            static void* allocate(size_t size);
            static void* reallocate(void* ptr, size_t size);
            static char* duplicate(const char* str);
        };
    }
}

#endif	/* UTILITIES_IO_XMLREADER_H */

