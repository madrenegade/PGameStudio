#include "serverthread.h"
#include "memprof/server.h"
#include "mainwindow.h"

ServerThread::ServerThread(memprof::server* server, QObject *parent) :
    QThread(parent), server(server)
{
}

ServerThread::~ServerThread()
{
}


void ServerThread::run()
{
    server->start_waiting_for_connection();

    while(!server->is_connection_established())
    {
        sleep(100);
    }

    exec();
}
