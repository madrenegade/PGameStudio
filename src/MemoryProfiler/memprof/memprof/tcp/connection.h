/* 
 * File:   connection.h
 * Author: madrenegade
 *
 * Created on September 7, 2011, 7:55 AM
 */

#ifndef MEMPROF_TCP_CONNECTION_H
#define	MEMPROF_TCP_CONNECTION_H

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

namespace memprof
{
    namespace tcp
    {

        class connection : public boost::enable_shared_from_this<connection>
        {
        public:
            typedef boost::shared_ptr<connection> pointer;
            
            static pointer create(boost::asio::io_service& io_service);
            
            boost::asio::ip::tcp::socket& get_socket();
            
            void start();
            
        private:
            connection(boost::asio::io_service& io_service);
            
            void handle_read(const boost::system::error_code& error, size_t bytesTransferred);
            
            boost::asio::ip::tcp::socket socket;
            boost::array<char, 4096> buffer;
        };
    }
}


#endif	/* MEMPROF_TCP_CONNECTION_H */

