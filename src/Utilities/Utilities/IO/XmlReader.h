/* 
 * File:   XmlReader.h
 * Author: madrenegade
 *
 * Created on September 22, 2011, 7:54 PM
 */

#ifndef UTILITIES_IO_XMLREADER_H
#define	UTILITIES_IO_XMLREADER_H

#include <boost/shared_ptr.hpp>
#include <sstream>

#include "Utilities/string.h"
#include "Utilities/IO/File.h"

#include "Utilities/IO/rapidxml.hpp"

namespace Utilities
{
    namespace IO
    {
        class XmlReader
        {
        public:
            typedef rapidxml::xml_document<> Document;
            typedef rapidxml::xml_node<> Node;
            
            XmlReader(const boost::shared_ptr<Memory::MemoryManager>& memory, const File& file);
            ~XmlReader();
            
            const Document* getDocument() const;
            
        private:
            boost::scoped_array<Memory::byte> data;
            Document doc;
        };
    }
}

#endif	/* UTILITIES_IO_XMLREADER_H */

