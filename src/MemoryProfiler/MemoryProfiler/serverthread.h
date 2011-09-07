#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>

namespace memprof
{
    class server;
}

class ServerThread : public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(memprof::server* server, QObject *parent = 0);
    virtual ~ServerThread();

protected:
    void run();

private:
    memprof::server* server;
};

#endif // SERVERTHREAD_H
