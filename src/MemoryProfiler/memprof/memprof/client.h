/*
 * File:   client.h
 * Author: madrenegade
 *
 * Created on September 6, 2011, 7:27 PM
 */

#ifndef MEMPROF_CLIENT_H
#define	MEMPROF_CLIENT_H

#include <string>
#include <boost/asio.hpp>

class StackTrace;

namespace memprof
{
    /**
     * memprof client which sends allocation data to the a server
     */
    class client
    {
    public:
        client(const char* const host);
        ~client();

        /**
         * notify the server that a new frame started
         */
        void begin_new_frame();

        /**
         * send allocation data to the server
         * @param stacktrace
         * @param bytes
         */
        void send_allocation_info(const StackTrace& stacktrace, const size_t bytes, const size_t poolID);

    private:
        void connect();

        const std::string host;

        boost::asio::io_service io_service;
        boost::shared_ptr<boost::asio::ip::tcp::socket> socket;

        bool connected;
    };
}

#endif	/* MEMPROF_CLIENT_H */

