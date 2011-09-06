/* 
 * File:   client.cpp
 * Author: madrenegade
 * 
 * Created on September 6, 2011, 7:27 PM
 */

#include "memprof/client.h"
#include <boost/asio.hpp>

#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <exception>

using boost::asio::ip::tcp;

namespace memprof
{

    client::client(const char* host)
    : host(host)
    {

    }

    client::~client()
    {

    }

    void client::connect()
    {
        RAW_LOG(INFO, "Connecting to server at %s", host.c_str());

        try
        {
            boost::asio::io_service io_service;
            tcp::resolver resolver(io_service);

            tcp::resolver::query query(host.c_str(), "1234");

            tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
            tcp::resolver::iterator end;

            socket.reset(new tcp::socket(io_service));

            boost::system::error_code error = boost::asio::error::host_not_found;
            
            while (error && endpoint_iterator != end)
            {
                socket->close();
                socket->connect(*endpoint_iterator++, error);
            }
            
            if (error)
            {
                throw boost::system::system_error(error);
            }
            
            RAW_LOG(INFO, "Connected to server at %s", host.c_str());
        }
        catch (const std::exception& ex)
        {
            RAW_LOG(ERROR, ex.what());
        }
    }
    
    void client::send_allocation_info(const std::type_info& type, const char* function, size_t bytes)
    {
        std::string message(type.name());
        message += "::" + std::string(function);
        
        boost::asio::write(*socket, boost::asio::buffer(message));
        
        RAW_LOG(INFO, "Sent data to server");
    }
}
