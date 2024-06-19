#ifndef RECVBOX_H
#define RECVBOX_H

#include <QImage>
#include <QWidget>
#include <QPainter>
#include "ChatBox.h"
#include <QImageReader>
#include <QTextDocument>

namespace Ui {
class Recvbox;
}

class Recvbox : public ChatBox
{
    Q_OBJECT

public:
    explicit Recvbox(QWidget *parent = nullptr);
    ~Recvbox();

////------------------------------------界面模块函数-------------------------------------------------------------
public:
    //处理气泡大小
    int handle_RecvBoxSize();
    //返回气泡高度
    int return_RecvBoxHeight();
    //处理头像
    int handle_HeadImg(const QString& imgpath) override;
protected:
    //处理大小变化事件
    virtual void resizeEvent(QResizeEvent *event) override;
////------------------------------------发送文字模块函数-------------------------------------------------------------
public:
    //处理发送的文字
    int handle_RecvBoxShowText(QString text);
////------------------------------------发送图片模块函数----------------------------------------------------------
public:
    //处理接收的图片
    int handle_RecvBoxShowImg(const QString& img);
    //处理接收的表情
    int handle_RecvBoxShowEmotion(const QString& emotion);
    //获取气泡文档并插入图片
    int handle_GetRecvBoxDocumentInsterImg(const QImage& image, const QString &path, const QSize& size);

private:
    int height; //气泡高度
    Ui::Recvbox *ui;
    QTextDocument* text_Doc;//气泡文档
};

#endif // RECVBOX_H
