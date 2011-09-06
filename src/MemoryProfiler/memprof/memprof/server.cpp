/* 
 * File:   server.cpp
 * Author: madrenegade
 * 
 * Created on September 6, 2011, 7:27 PM
 */

#include "memprof/server.h"

#include <boost/asio.hpp>
#include <exception>

#include <glog/logging.h>
#include <glog/raw_logging.h>

using boost::asio::ip::tcp;

namespace memprof
{

    server::server(unsigned short port)
    : port(port)
    {

    }

    server::~server()
    {

    }

    void server::run()
    {
        try
        {
            boost::asio::io_service io_service;

            tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
            
            RAW_LOG(INFO, "memprof server waiting for connections...");

            while (true)
            {
                tcp::socket socket(io_service);
                acceptor.accept(socket);

                RAW_LOG(INFO, "Client connected");
            }
            
            RAW_LOG(INFO, "server stopped waiting for connections");
        }
        catch (const std::exception& ex)
        {
            RAW_LOG(ERROR, ex.what());
        }
    }
}

