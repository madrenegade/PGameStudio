/* 
 * File:   server.h
 * Author: madrenegade
 *
 * Created on September 6, 2011, 7:27 PM
 */

#ifndef MEMPROF_SERVER_H
#define	MEMPROF_SERVER_H

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
        
        void run();
        
    private:
        const unsigned short port;
    };
}

#endif	/* MEMPROF_SERVER_H */

