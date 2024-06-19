#ifndef RECVFILEBOX_H
#define RECVFILEBOX_H

#include <QDir>
#include <QWidget>
#include <QPainter>
#include <QProcess>
#include "ChatBox.h"
#include <QMouseEvent>
#include <QDesktopServices>

namespace Ui {
class recvFilebox;
}

class recvFilebox : public ChatBox
{
    Q_OBJECT

public:
    explicit recvFilebox(QWidget *parent = nullptr);
    ~recvFilebox();

public:
    //更新接收进度条下载信息
    int set_ReceiveRecvsize(int recvsize);
    //处理头像
    int handle_HeadImg(const QString& imgpath) override;
    //设置文件信息
    int set_FileInfo(const QString& name,const qint64& size);
protected:
    //双击事件
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
signals:
    //请求服务器发送文件
    void handle_RequestServerSendingFile();

private:
    Ui::recvFilebox *ui;
    int fileSize;    //文件大小
    bool filestate;  //文件状态
    QString filePath;//文件路径
};

#endif // RECVFILEBOX_H
