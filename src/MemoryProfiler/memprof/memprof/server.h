/* 
 * File:   server.h
 * Author: madrenegade
 *
 * Created on September 6, 2011, 7:27 PM
 */

#ifndef MEMPROF_SERVER_H
#define	MEMPROF_SERVER_H

#include "memprof/tcp/connection.h"

namespace memprof
{
    /**
     * memprof server which evaluates data sent by a client
     */
    class server
    {
    public:
        server(unsigned short port = 1234);
        ~server();
        
        void register_listener(change_listener* listener);
        
        void start_waiting_for_connection();
        bool is_connection_established() const;
        
    private:
        const unsigned short port;
        
        bool connection_established;
        
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor;
        
        std::list<change_listener*> registeredListeners;
        
        void handle_accept(tcp::connection::pointer new_connection, const boost::system::error_code& error);
    };
}

#endif	/* MEMPROF_SERVER_H */

