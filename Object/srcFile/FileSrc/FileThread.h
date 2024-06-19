/*#ifndef FILETHREAD_H
#define FILETHREAD_H

#include <QThread>
#include <QWidget>
#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

//消息类型
enum FileType{
    FileInfo,   //文件信息
    FileData,   //文件数据
};

class FileThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit FileThread(QObject *parent = nullptr);
    ~FileThread();

    //获取传输的文件
    bool get_FilePath();
    //线程执行内容
    virtual void run() override;
    //获取文件信息
    const qint64& get_UserSizeinfo(const QString &Type);
    const QString& get_UserStrinfo(const QString &Type);
    //链接服务器
    void connectToServer();
    //下载服务器数据
    void readServerMsg();

    void fileDataRead();

signals:
    //文件信号
    void newFile();
    //下载进度更新信号
    void newRecvsize(int recvsize);

private:
    QFile *file;             //文件
    QWidget *Widget;         //文件打开窗口
    qint64 file_Size;        //文件大小
    QString file_Path;       //文件路径
    QString file_Name;       //文件名称
    long file_progressByte;  //文件下载进度
    qint64 file_RecvSize;    //已接收大小
    qint64 file_SendSize;    //已发送大小
    bool file_isDownloading;                  //是否正在下载
    QTcpSocket* file_TcpSocket;               //文件下载TCP链接
    QSharedPointer<QFileInfo> file_FileInfo;  //文件信息

};

#endif // FILETHREAD_H*/
