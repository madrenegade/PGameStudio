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
        
        connection::~connection()
        {
            RAW_LOG(INFO, "Destroying client connection");
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
            RAW_LOG(INFO, "handle_read");
            
            if (!error)
            {
                RAW_LOG(INFO, "no error");
                sample sample;

                boost::iostreams::basic_array_source<char> device(buffer.c_array(), buffer.size());
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);

                boost::archive::binary_iarchive ia(s);
                ia >> sample;

                RAW_LOG(INFO, "notifying listeners");
                
                notify_listeners(sample);
                
                start();
            }
        }

        void connection::notify_listeners(const sample& sample)
        {
            switch(sample.getType())
            {
                case sample_type::new_frame:
                    notify_listeners_about_new_frame();
                    break;
                    
                case sample_type::allocation:
                    notify_listeners_about_allocation(sample);
                    break;
            }
        }

        void connection::notify_listeners_about_new_frame()
        {
            std::for_each(listeners.begin(), listeners.end(), [](change_listener* listener) { 
                listener->on_new_frame(); 
            });
        }

        void connection::notify_listeners_about_allocation(const sample& sample)
        {
            std::for_each(listeners.begin(), listeners.end(), [&sample](change_listener* listener) { 
                listener->on_allocation(sample); 
            });
        }
    }
}

