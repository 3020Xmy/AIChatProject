#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include <QObject>
#include <QRunnable>
#include <QUdpSocket>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>

class UdpThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ~UdpThread();
    explicit UdpThread(QObject *parent = nullptr);
    explicit UdpThread(QUdpSocket *socket, QObject *parent = nullptr);
    virtual void run() override;

////-----------------------------------发送文件模块函数------------------------------------------------------
public:
    //设置文件信息
    int handle_SetFileInfo();
    //获取传输的文件
    bool handle_getFilePath();
    //获取文件大小
    const qint64& handle_GetFileSize();
    //获取文件名称
    const QString& handle_GetFileName();
    //获取文件路径
    const QString& handle_GetFilePath();


private:
    bool ok;    //线程状态
    QFile *file;      //文件
    QWidget *Widget;  //文件打开窗口
    qint64 file_Size; //文件大小
    QString file_Path;//文件路径
    QString file_Name;//文件名称
    QUdpSocket* file_SendingObj;    //文件发送对象
    QSharedPointer<QFileInfo> file_FileInfo;  //文件信息
};

#endif // UDPTHREAD_H
