/* 
 * File:   PropertyManager.h
 * Author: madrenegade
 *
 * Created on September 7, 2011, 3:32 PM
 */

#ifndef UTILITIES_PROPERTIES_PROPERTYMANAGER_H
#define	UTILITIES_PROPERTIES_PROPERTYMANAGER_H

#include <boost/program_options.hpp>
#include <list>

namespace po = boost::program_options;

namespace Utilities
{
    namespace Properties
    {
        class PropertyChangeListener;
        
        class PropertyManager
        {
        public:
            PropertyManager();
            
            /**
             * Add some options description. This merges the already added descriptions with this one.
             * This method must be called before parse
             * @param options - the options to add
             */
            void addOptions(const po::options_description& options);
            
            /**
             * parses options from the command line
             * @param argc
             * @param argv
             */
            void parse(int argc, char** argv);
            
            /**
             * parse a config file
             * @param filename - the name of the file to parse
             */
            void parse(const char* filename);
            
            /**
             * add a listener which is notified when a property is changed
             * @param listener - the listener to notify
             * @param property
             */
            void addListener(PropertyChangeListener* listener, const char* property);
            void removeListener(PropertyChangeListener* listener, const char* property);
            
            /**
             * return a property casted to the specified type
             * if casting fails an exception is thrown
             * @param name
             * @return the property value
             */
            template<typename T>
            const T& get(const char* name) const
            {
               return boost::any_cast<T>(properties.at(name));
            }
            
            /**
             * set the value of an existing property
             * throws an exception if the property does not exist or the type is invalid
             * @param name
             * @param value
             */
            void set(const char* name, const boost::any& value);
            
        private:
            /**
             * copies all properties from the variables map into the property map
             * @param vm - the variables map to copy from
             */
            void addPropertiesFrom(const po::variables_map& vm);
            
            /**
             * add a property to the property map if it does not exist
             * if the property already exists an exception is thrown
             * @param name
             * @param value
             */
            void addProperty(const std::string& name, const boost::any& value);
            
            bool propertyExists(const std::string& name) const;
            
            void notifyListenersAboutChangeOf(const std::string& name);
            
            po::options_description options;
            
            typedef std::map<std::string, boost::any> PropertyMap;
            PropertyMap properties;
            
            typedef std::map<std::string, std::list<PropertyChangeListener*> > ListenerMap;
            ListenerMap listeners;
        };
    }
}


#endif	/* UTILITIES_PROPERTIES_PROPERTYMANAGER_H */

