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

namespace Utilities
{
    namespace Properties
    {

        PropertyManager::PropertyManager()
            : options("Allowed options")
        {

        }

        PropertyManager::~PropertyManager()
        {
        }

        void PropertyManager::addOptions(const po::options_description& options)
        {
            this->options.add(options);
        }

        void PropertyManager::parse(int argc, char** argv)
        {
            options.add_options()
            ("argc", po::value<int>(), "Argument count")
            ("argv0", po::value<std::string>(), "Argument 0")
            ("v", po::value<int>(), "Verbosity level for glog")
            ("minloglevel", po::value<int>(), "Minimum log level for glog");

            po::variables_map vm;
            po::store(po::parse_command_line(argc, argv, options), vm);
            po::notify(vm);

            addPropertiesFrom(vm);

            set("argc", argc);
            set("argv0", std::string(argv[0]));
        }

        void PropertyManager::parse(const char* const filename)
        {
            VLOG(1) << "Parsing config file " << filename;

            po::variables_map vm;

            std::ifstream in(filename);

            if(!in)
            {
                LOG(WARNING) << "Could not open config file " << filename;
                return;
            }

            po::store(po::parse_config_file(in, options), vm);
            po::notify(vm);

            addPropertiesFrom(vm);
        }

        void PropertyManager::addListener(PropertyChangeListener* const listener, const char* const property)
        {
            listeners[property].push_front(listener);
        }

        void PropertyManager::removeListener(PropertyChangeListener* const listener, const char* const property)
        {
            listeners[property].remove(listener);
        }

        void PropertyManager::set(const char* const name, const boost::any& value)
        {
            DCHECK(propertyExists(name));
            DCHECK(properties[name].type() == value.type());

            properties[name] = value;

            notifyListenersAboutChangeOf(name);
        }

        void PropertyManager::addPropertiesFrom(const po::variables_map& vm)
        {
            std::for_each(vm.begin(), vm.end(), [&] (const std::pair<std::string, boost::program_options::variable_value>& i) {
                addProperty(i.first, i.second);
            });
        }

        void PropertyManager::addProperty(const std::string& name, const boost::program_options::variable_value& value)
        {
            if (propertyExists(name))
            {
                // the property already exists if another config file has been loaded before
                // to prevent overwriting the current value with the default value we must return here
                return;
            }

            properties[name] = value.value();
        }

        bool PropertyManager::propertyExists(const std::string& name) const
        {
            return properties.find(name) != properties.end();
        }

#ifdef DEBUG
        void PropertyManager::assertPropertyExists(const std::string& name) const
        {
            if(!propertyExists(name))
            {
                throw std::logic_error("Property does not exist: " + name);
            }
        }
#endif

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


