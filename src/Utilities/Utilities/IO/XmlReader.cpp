/* 
 * File:   XmlReader.cpp
 * Author: madrenegade
 * 
 * Created on September 22, 2011, 7:54 PM
 */

#include "Utilities/IO/XmlReader.h"
#include "File.h"

extern "C"
{
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
}

#include <glog/logging.h>
#include <stdexcept>

namespace Utilities
{
    namespace IO
    {

        struct XmlDocDeleter
        {

            void operator()(xmlDocPtr doc)
            {
                xmlFreeDoc(doc);
            }
        };

        struct XPathContextDeleter
        {

            void operator()(xmlXPathContextPtr context)
            {
                xmlXPathFreeContext(context);
            }
        };

        struct XPathObjectDeleter
        {

            void operator()(xmlXPathObjectPtr xpathObject)
            {
                xmlXPathFreeObject(xpathObject);
            }
        };

        Memory::MemoryManager* XmlReader::memory = 0;

        XmlReader::XmlReader(const boost::shared_ptr<Memory::MemoryManager>& memory, const File& file)
        {
            XmlReader::memory = memory.get();

//            if (xmlMemSetup(&XmlReader::deallocate, &XmlReader::allocate, &XmlReader::reallocate, &XmlReader::duplicate) != 0)
//            {
//                LOG(FATAL) << "Could not set libxml2 memory functions";
//            }

            xmlInitParser();
            doc.reset(xmlParseMemory(file.getData(), file.getSize()), XmlDocDeleter());

            if (!doc)
            {
                LOG(FATAL) << "Could not parse file";
            }

            context.reset(xmlXPathNewContext(doc.get()), XPathContextDeleter());

            if (!context)
            {
                LOG(FATAL) << "Could not create new xpath context";
            }


        }

        XmlReader::~XmlReader()
        {
            xmlCleanupParser();
        }

        void XmlReader::evaluate(const unsigned char* xpath, std::vector<String, Utilities::Memory::STLAllocator<String >> &results)
        {
            std::shared_ptr<xmlXPathObject> xpathObject(xmlXPathEvalExpression(xpath, context.get()), XPathObjectDeleter());

            if (!xpathObject)
            {
                LOG(FATAL) << "Could not evaluate xpath expression: " << xpath;
            }

            xmlNodeSetPtr nodes = xpathObject->nodesetval;

            unsigned int numNodes = (nodes) ? nodes->nodeNr : 0;

            results.resize(numNodes);

            for (unsigned int i = 0; i < numNodes; ++i)
            {
                xmlNodePtr current = nodes->nodeTab[i];

                switch (current->type)
                {
                    case XML_ATTRIBUTE_NODE:
                    {
                        String content(reinterpret_cast<const char*> (xmlGetProp(current->parent, current->name)));
                        results[i] = content;
                    }
                        break;

                    case XML_ELEMENT_NODE:
                    {
                        String content(reinterpret_cast<const char*> (xmlNodeListGetString(doc.get(), current->children, 1)));
                        results[i] = content;
                    }
                        break;

                    default:
                        throw std::runtime_error("Unhandled node type");
                }
            }
        }

        void XmlReader::deallocate(void* ptr)
        {
//            memory->rawDeallocate(ptr);
        }

        void* XmlReader::allocate(size_t size)
        {
#ifdef DEBUG
            return memory->rawAllocate<Memory::byte>(size, StackTrace());
#else
            return memory->rawAllocate<Memory::byte>(size);
#endif
        }

        void* XmlReader::reallocate(void* ptr, size_t size)
        {
            return 0;
        }

        char* XmlReader::duplicate(const char* str)
        {
            return 0;
        }
    }
}


