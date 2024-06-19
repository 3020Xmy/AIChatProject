#ifndef SENDFILEBOX_H
#define SENDFILEBOX_H

#include <QUrl>
#include <QWidget>
#include <QPainter>
#include <QProcess>
#include "ChatBox.h"
#include <QMouseEvent>
#include <QDesktopServices>

namespace Ui {
class sendFilebox;
}

class sendFilebox : public ChatBox
{
    Q_OBJECT

public:
    explicit sendFilebox(QWidget *parent = nullptr);
    ~sendFilebox();

public:
    //更新进度条下载信息
    int set_Recvsize(int recvsize);
    //设置文件路径
    int set_FilePath(const QString& path);
    //设置文件信息
    int set_FileInfo(const QString& name,const qint64& size);
    //处理头像
    int handle_HeadImg(const QString& imgpath) override;

protected:
    //鼠标双击事件
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::sendFilebox *ui;
    int fileSize;
    QString filePath;
};

#endif // SENDBOX_H
