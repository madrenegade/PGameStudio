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

namespace memprof
{
    /**
     * memprof client which sends allocation data to the a server
     */
    class client
    {
    public:
        client(const char* host);
        ~client();
        
        void connect();
        
        void send_allocation_info(const std::type_info& type, const char* function, size_t bytes);
        
    private:
        const std::string host;
        
        boost::scoped_ptr<boost::asio::ip::tcp::socket> socket;
    };
}

#endif	/* MEMPROF_CLIENT_H */

