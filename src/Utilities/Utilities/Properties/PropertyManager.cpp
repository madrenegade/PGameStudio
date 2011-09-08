/* 
 * File:   PropertyManager.cpp
 * Author: madrenegade
 * 
 * Created on September 7, 2011, 3:32 PM
 */

#include "Utilities/Properties/PropertyManager.h"
#include "Utilities/Properties/PropertyChangeListener.h"
#include <boost/program_options/parsers.hpp>
#include <fstream>

#include <glog/logging.h>

namespace Utilities
{
    namespace Properties
    {

        PropertyManager::PropertyManager()
        : options("Allowed options")
        {

        }

        void PropertyManager::addOptions(const po::options_description& options)
        {
            this->options.add(options);
        }

        void PropertyManager::parse(int argc, char** argv)
        {
            VLOG(1) << "Parsing command line arguments";
            
            po::variables_map vm;
            po::store(po::parse_command_line(argc, argv, options), vm);
            po::notify(vm);

            addPropertiesFrom(vm);
        }

        void PropertyManager::parse(const char* filename)
        {
            VLOG(1) << "Parsing config file " << filename;
            
            po::variables_map vm;

            std::ifstream in(filename);
            
            if(!in)
            {
                LOG(WARNING) << "Could not open config file";
            }
            
            po::store(po::parse_config_file(in, options), vm);
            po::notify(vm);

            addPropertiesFrom(vm);
        }

        void PropertyManager::addListener(PropertyChangeListener* listener, const char* property)
        {
            listeners[property].push_front(listener);
        }

        void PropertyManager::removeListener(PropertyChangeListener* listener, const char* property)
        {
            listeners[property].remove(listener);
        }

        void PropertyManager::set(const char* name, const boost::any& value)
        {
            DCHECK(propertyExists(name));
            DCHECK(properties[name].type() == value.type());
            
            VLOG(2) << "Setting property " << name;

            properties[name] = value;

            notifyListenersAboutChangeOf(name);
        }

        void PropertyManager::addPropertiesFrom(const po::variables_map& vm)
        {
            auto fn = [&] (const std::pair<std::string, boost::any>& i){
                addProperty(i.first, i.second);
            };

            std::for_each(vm.begin(), vm.end(), fn);
        }

        void PropertyManager::addProperty(const std::string& name, const boost::any& value)
        {
            if (!propertyExists(name))
            {
                throw std::logic_error("Property not found");
            }

            properties[name] = value;
        }

        bool PropertyManager::propertyExists(const std::string& name) const
        {
            return properties.find(name) != properties.end();
        }

        void PropertyManager::notifyListenersAboutChangeOf(const std::string& name)
        {
            if (listeners.find(name) == listeners.end()) return;

            std::list<PropertyChangeListener*>& listeners = this->listeners.at(name);
            
            auto fn = [&](PropertyChangeListener * listener) {
                listener->onPropertyChanged(name, properties[name]);
            };

            std::for_each(listeners.begin(), listeners.end(), fn);
        }
    }
}


