#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QObject>
#include <QRunnable>
#include <QJsonObject>
#include <QJsonDocument>

class TcpThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ~TcpThread();
   virtual void run() override;
   explicit TcpThread(QObject *parent = nullptr);
   explicit TcpThread(const QString &number, QObject *parent = nullptr);

public:
   //处理服务端返回的Json
   void execute_JsonOperate(QByteArray jsondata);
   //设置传输的Json数据
   QJsonObject set_PackageJSoninOperate(const QString &type, const QString &data, const QString &number);

signals:
   //返回服务器验证信息给主线程处理
   void return_TestingMessage(bool Ok);
   //提示主线程把信息发送给服务端
   void sending_inServer(QByteArray jsondata);

private:
   QString read_type;       //读取到的操作类型字段
   QString read_data;       //读取到的数据字段
   QString read_number;     //读取到的账号字段
   QJsonObject jsonObject;      //传输的json数据
   QString user_Number = "";    //登录的账号
};

#endif // TCPTHREAD_H
