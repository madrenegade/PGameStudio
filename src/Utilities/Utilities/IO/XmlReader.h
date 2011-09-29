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
            typedef rapidxml::xml_attribute<> Attribute;

            XmlReader(const boost::shared_ptr<Memory::MemoryManager>& memory,
                      const Utilities::Memory::pool_id pool, const File::Handle& file);
            ~XmlReader();

            const Document* getDocument() const;

        private:
            const boost::shared_array<Memory::byte> data;
            boost::shared_ptr<Document> doc;
        };
    }
}

#endif	/* UTILITIES_IO_XMLREADER_H */

