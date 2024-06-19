#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include <QRunnable>
#include <QObject>

class UdpThread : public QRunnable
{
    Q_OBJECT
public:
    UdpThread();
};

#endif // UDPTHREAD_H
