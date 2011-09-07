/* 
 * File:   client.cpp
 * Author: madrenegade
 * 
 * Created on September 6, 2011, 7:27 PM
 */

#include "memprof/client.h"
#include "memprof/sample.h"
#include <boost/asio.hpp>

#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <exception>
#include <list>

#include "StackTrace.h"

#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/stream.hpp>

using boost::asio::ip::tcp;

namespace memprof
{

    client::client(const char* host)
    : host(host), connected(false)
    {

    }

    client::~client()
    {
        if(connected) 
        {
            socket->shutdown(socket->shutdown_both);
            socket->close();
        } 
    }

    void client::connect()
    {
        RAW_LOG(INFO, "Connecting to server at %s", host.c_str());

        try
        {
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

            connected = true;
            
            RAW_LOG(INFO, "Connected to server at %s", host.c_str());
        }
        catch (const std::exception& ex)
        {
            RAW_LOG(ERROR, ex.what());
            RAW_LOG(WARNING, "Memory profiling is not available");
        }
    }

    void client::send_allocation_info(const StackTrace& stacktrace, size_t bytes)
    {
        if(!connected) return;
           
        char buffer[4096];
        boost::iostreams::basic_array_sink<char> sr(buffer);
        boost::iostreams::stream< boost::iostreams::basic_array_sink<char> > source(sr);
        
        const sample sample(stacktrace, bytes);

        boost::archive::binary_oarchive oa(source);
        oa << sample;

        boost::asio::write(*socket, boost::asio::buffer(buffer));
    }
}
