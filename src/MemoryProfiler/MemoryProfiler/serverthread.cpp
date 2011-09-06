#include "serverthread.h"
#include "memprof/server.h"

ServerThread::ServerThread(QObject *parent) :
    QThread(parent)
{
    server = new memprof::server;
}

ServerThread::~ServerThread()
{
    delete server;
}


void ServerThread::run()
{
    server->run();
}
