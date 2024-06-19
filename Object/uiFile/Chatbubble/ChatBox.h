#ifndef CHATBOX_H
#define CHATBOX_H

#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QPainter>

class ChatBox : public QWidget
{
public:
    ~ChatBox();
    ChatBox(QWidget *parent = nullptr);
    //处理头像
    virtual int handle_HeadImg(const QString &imgpath) = 0;
    //设置头像属性
    virtual int handle_SetHeadImgAttribute(QPixmap* pixmap, QPixmap* attribute);
};

#endif // CHATBOX_H
