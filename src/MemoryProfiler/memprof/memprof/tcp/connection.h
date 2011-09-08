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
#include <list>

class StackTrace;

namespace memprof
{
    class change_listener;
    class sample;
    
    namespace tcp
    {

        class connection : public boost::enable_shared_from_this<connection>
        {
        public:
            typedef boost::shared_ptr<connection> pointer;

            static pointer create(boost::asio::io_service& io_service,
                                  const std::list<change_listener*>& listeners);

            boost::asio::ip::tcp::socket& get_socket();

            void start();
            
            virtual ~connection();

        private:
            connection(boost::asio::io_service& io_service,
                       const std::list<change_listener*>& listeners);

            void handle_read(const boost::system::error_code& error, size_t bytesTransferred);
            
            void notify_listeners(const sample& sample);
            
            void notify_listeners_about_new_frame();
            void notify_listeners_about_allocation(const sample& sample);

            boost::asio::ip::tcp::socket socket;
            boost::array<char, 4096 > buffer;
            
            typedef std::list<change_listener*> ListenerList;
            ListenerList listeners;
        };
    }
}


#endif	/* MEMPROF_TCP_CONNECTION_H */

