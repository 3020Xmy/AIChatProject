#ifndef FILEINFO_H
#define FILEINFO_H

#include <QObject>
#include <QFile>
#include <QFileInfo>

class FileInfo : public QObject
{
    Q_OBJECT
public:
    explicit FileInfo();
    ~FileInfo();
    //获取文件信息
    const QString& get_UserInfo(const QString &Type);

private:
    QFile file;             //文件
    QWidget *Widget;        //文件打开窗口
    QString file_Size;       //文件大小
    QString file_Path;      //文件路径
    QString file_Name;      //文件名称
    QString file_RecvSize;   //已接收大小
    QString file_SendSize;   //已发送大小
    QSharedPointer<QFileInfo> file_FileInfo;  //文件信息
};

#endif // FILEINFO_H
