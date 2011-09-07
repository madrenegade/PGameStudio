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

        class PropertyChangeListener
        {
        public:
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

