#ifndef connect_H
#define connect_H

#include <QObject>
#include <QconnectInfo>
#include <QconnectAddress>

class connect : public QObject
{
    Q_OBJECT
public:
    explicit connect();
    ~connect();

    //获取本机IPv4地址
    void get_HoatIPv4();


private:
    QString Local_connectName;      //本机名
    quint16 Local_connectPort;      //本机端口
    QString Local_HoatIPv4;      //本机IPv4地址
    QconnectInfo Local_connectInfo;    //本机信息
};

extern connect my_connect;   //声明全局变量

#endif // connect_H
