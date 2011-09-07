/* 
 * File:   connection.cpp
 * Author: madrenegade
 * 
 * Created on September 7, 2011, 7:55 AM
 */

#include "memprof/tcp/connection.h"
#include "memprof/change_listener.h"
#include "memprof/sample.h"
#include "StackTrace.h"

#include <boost/bind.hpp>
#include <glog/logging.h>
#include <glog/raw_logging.h>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/stream.hpp>

namespace memprof
{
    namespace tcp
    {

        connection::pointer connection::create(boost::asio::io_service& io_service,
                                               const std::list<change_listener*>& listeners)
        {
            return pointer(new connection(io_service, listeners));
        }

        connection::connection(boost::asio::io_service& io_service,
                               const std::list<change_listener*>& listeners)
        : socket(io_service), listeners(listeners)
        {

        }

        boost::asio::ip::tcp::socket& connection::get_socket()
        {
            return socket;
        }

        void connection::start()
        {
            RAW_LOG(INFO, "Starting client connection");

            boost::asio::async_read(socket, boost::asio::buffer(buffer),
                boost::bind(&connection::handle_read, shared_from_this(),
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
        }

        void connection::handle_read(const boost::system::error_code& error, size_t bytesTransferred)
        {
            if (!error)
            {
                sample sample;

                boost::iostreams::basic_array_source<char> device(buffer.c_array(), buffer.size());
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);

                boost::archive::binary_iarchive ia(s);
                ia >> sample;
                
                notify_listeners(sample);
            }
        }
        
        void connection::notify_listeners(const sample& sample)
        {
            for(ListenerList::iterator i = listeners.begin(); i != listeners.end(); ++i)
            {
                (*i)->on_change(sample);
            }
        }
    }
}

