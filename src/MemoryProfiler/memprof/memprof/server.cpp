/* 
 * File:   server.cpp
 * Author: madrenegade
 * 
 * Created on September 6, 2011, 7:27 PM
 */

#include "memprof/server.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <exception>

#include <glog/logging.h>
#include <glog/raw_logging.h>

namespace memprof
{

    server::server(unsigned short port)
    : port(port), connection_established(false),
        io_service(), acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {

    }

    server::~server()
    {

    }

    void server::start_waiting_for_connection()
    {
        RAW_LOG(INFO, "memprof server waiting for connections...");
        
        tcp::connection::pointer new_connection = tcp::connection::create(io_service);

        acceptor.async_accept(new_connection->get_socket(),
            boost::bind(&server::handle_accept, this, new_connection,
            boost::asio::placeholders::error));
        
        io_service.run();
    }
    
    bool server::is_connection_established() const
    {
        return connection_established;
    }

    void server::handle_accept(tcp::connection::pointer new_connection, const boost::system::error_code& error)
    {
        if (!error)
        {
            RAW_LOG(INFO, "Client connected");
            
            connection_established = true;
            new_connection->start();
            start_waiting_for_connection();
        }
        else
        {
            RAW_LOG(INFO, "Error while accepting client");
        }
    }
}

