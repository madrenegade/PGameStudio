/* 
 * File:   connection.cpp
 * Author: madrenegade
 * 
 * Created on September 7, 2011, 7:55 AM
 */

#include "memprof/tcp/connection.h"
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

        connection::pointer connection::create(boost::asio::io_service& io_service)
        {
            return pointer(new connection(io_service));
        }

        connection::connection(boost::asio::io_service& io_service)
        : socket(io_service)
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
                StackTrace stacktrace(false);

                boost::iostreams::basic_array_source<char> device(buffer.c_array(), buffer.size());
                boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s(device);

                boost::archive::binary_iarchive ia(s);
                ia >> stacktrace;

                typedef std::list<StackFrame> Frames;

                const Frames& frames = stacktrace.getFrames();

                RAW_LOG_INFO("STACKFRAME_START");

                for (Frames::const_iterator i = frames.begin(); i != frames.end(); ++i)
                {
                    RAW_LOG_INFO("Function: %s", i->getFunction().c_str());
                }

                RAW_LOG_INFO("STACKFRAME_END");
            }
        }
    }
}

