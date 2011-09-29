/*
 * File:   PropertyChangeListener.h
 * Author: madrenegade
 *
 * Created on September 7, 2011, 3:34 PM
 */

#ifndef UTILITIES_PROPERTIES_PROPERTYCHANGELISTENER_H
#define	UTILITIES_PROPERTIES_PROPERTYCHANGELISTENER_H

#include <boost/any.hpp>

namespace Utilities
{
    namespace Properties
    {
        /**
         * Listener interface used by \ref Utilities::Properties::PropertyManager "the property manager class".
         */
        class PropertyChangeListener
        {
        public:
            /**
             * This method is automatically called by \ref Utilities::Properties::PropertyManager "the property manager class"
             * when the value of a property has changed.
             * @param name - The name of the property who's value has changed.
             * @param value - The new value of the property.
             */
            virtual void onPropertyChanged(const std::string& name,
                                           const boost::any& value) = 0;

        protected:

            PropertyChangeListener()
            {
            }
        };
    }
}

#endif	/* UTILITIES_PROPERTIES_PROPERTYCHANGELISTENER_H */

