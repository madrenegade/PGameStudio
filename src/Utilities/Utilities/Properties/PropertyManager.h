/*
 * File:   PropertyManager.h
 * Author: madrenegade
 *
 * Created on September 7, 2011, 3:32 PM
 */

#ifndef UTILITIES_PROPERTIES_PROPERTYMANAGER_H
#define	UTILITIES_PROPERTIES_PROPERTYMANAGER_H

#include "Utilities/functions.h"
#include <boost/program_options.hpp>
#include <list>

#include <glog/logging.h>

namespace po = boost::program_options;

namespace Utilities
{
    namespace Properties
    {
        class PropertyChangeListener;
        // TODO: make property manager thread safe
        /**
         * A class for managing program options. This includes specifying which options are
         * allowed and loading settings from the command line or from ini-Files.
         */
        class PropertyManager
        {
        public:
            typedef std::shared_ptr<PropertyManager> Ptr;

            PropertyManager();
            ~PropertyManager();

            /**
             * Add some options description. This merges the already added descriptions with this one.
             * This method must be called before parse.
             * @param options - The options to add.
             */
            void addOptions(const po::options_description& options);

            /**
             * Parse options from the command line.
             * After parsing the properties "argv0" and "argc"
             * are automatically added. The types of the properties are
             * std::string and int.
             * @param argc - The amount of arguments.
             * @param argv - The argument values.
             */
            void parse(const int argc, char** argv);

            /**
             * Parse a config file.
             * @param filename - The name of the file to parse.
             */
            void parse(const char* const filename);

            /**
             * Add a listener which is notified when a property is changed.
             * @param listener - The listener to notify.
             * @param property - The name of the property to register the listener with.
             */
            void addListener(PropertyChangeListener* const listener, const char* const property);
            void removeListener(PropertyChangeListener* const listener, const char* const property);

            /**
             * Return a property casted to the specified type.
             * If casting fails an exception is thrown.
             * @param name - The name of the property to retreive.
             * @return The property value casted to type T.
             */
            template<typename T>
            T get(const char* const name) const
            {
#ifdef DEBUG
                assertPropertyExists(DCHECK_NOTNULL(name));

                try
                {
                    return boost::any_cast<T>(properties.at(name));
                }
                catch(const boost::bad_any_cast& ex)
                {
                    LOG(ERROR) << "Could not cast property "
                               << name << " to type "
                               << Utilities::demangle(typeid(T).name()) << std::endl
                               << " (expected " << Utilities::demangle(properties.at(name).type().name()) << ")";
                    throw;
                }
#else
                return boost::any_cast<T>(properties.at(name));
#endif
            }

            /**
             * Set the value of an existing property.
             * Throws an exception if the property does not exist or the type is invalid.
             * @param name - The name of the property to set.
             * @param value - The property value.
             */
            void set(const char* const name, const boost::any& value);

        private:
            /**
             * Copy all properties from the variables map into the property map.
             * @param vm - The variables map to copy from.
             */
            void addPropertiesFrom(const po::variables_map& vm);

            /**
             * Add a property to the property map if it does not exist.
             * If the property already exists an exception is thrown.
             * @param name - The name of the property.
             * @param value - The property value.
             */
            void addProperty(const std::string& name, const boost::program_options::variable_value& value);

            bool propertyExists(const std::string& name) const;

#ifdef DEBUG
            void assertPropertyExists(const std::string& name) const;
#endif

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

