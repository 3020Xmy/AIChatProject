#ifndef SENDBOX_H
#define SENDBOX_H

#include <QImage>
#include <QWidget>
#include <QPainter>
#include "ChatBox.h"
#include <QImageReader>
#include <QTextDocument>

namespace Ui {
class Sendbox;
}

class Sendbox : public ChatBox
{
    Q_OBJECT

public:
    explicit Sendbox(QWidget *parent = nullptr);
    ~Sendbox();

////------------------------------------界面模块函数-------------------------------------------------------------
public:
    //返回气泡高度
    int return_SendBoxHeight();
    //处理气泡大小
    int handle_SendBoxMarginsSize();
    //处理头像
    int handle_HeadImg(const QString &imgpath) override;
protected:
    //处理大小变化事件
    virtual void resizeEvent(QResizeEvent *event) override;
////------------------------------------发送图片模块函数----------------------------------------------------------
public:
    //处理发送的图片
    int handle_SendBoxShowImg(const QString& img);
    //处理发送的表情
    int handle_SendBoxShowEmotion(const QString& emotion);
    //获取气泡文档并插入图片
    int handle_GetSendBoxDocumentInsterImg(const QImage& image, const QString &path, const QSize& size);
////------------------------------------发送文字模块函数-------------------------------------------------------------
public:
    //处理发送的文字
    int handle_SendBoxShowText(QString text);

private:
    int height;     //气泡高度
    Ui::Sendbox *ui;
    QTextDocument* text_Doc;//气泡文档
};



#endif // SENDBOX_H
