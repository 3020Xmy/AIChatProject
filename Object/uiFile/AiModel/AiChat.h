#ifndef AICHAT_H
#define AICHAT_H

#include <QFile>
#include <QWidget>
#include <QScrollBar>
#include <QMouseEvent>
#include <QThreadPool>
#include "srcFile/USER.h"
#include "srcFile/NetWork.h"
#include <QNetworkInterface>
#include "srcFile/AiSrc/AI.h"
#include "uiFile/Chatbubble/Sendbox.h"
#include "uiFile/Chatbubble/Recvbox.h"
#include "srcFile/AiSrc/AiThread.h"

namespace Ui {
class AiChat;
}

class AiChat : public QWidget
{
    Q_OBJECT

public:
    explicit AiChat(QWidget *parent = nullptr);
    ~AiChat(); 
////------------------------------------Ai模块函数-------------------------------------------------------------
public:
    //设置机器人信息
    int set_AiChatinAiInfo(const QString &headPath,const QString &name,const QString &sign);
////------------------------------------界面模块函数-------------------------------------------------------------
public:
    //初始化界面
    int init_AiChatWidgte();
public slots:
    //设置窗口消息
    int new_AiChatWidgetInfo();
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //消息发送按钮
    void on_sending_Btn_clicked();
    //Top关闭界面函数
    void on_close_Btntop_clicked();
    //Bottom关闭界面函数
    void on_close_Btnbottom_clicked();
    //处理消息回复
    int get_Aianswer(const QString &response);
////------------------------------------事件模块函数-------------------------------------------------------------
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::AiChat *ui;
    bool move_Ok;         //是否移动
    QPoint move_point;    //移动的距离
    AiThread *ai_Thread;     //Ai对话线程
};

#endif // FRIENDCHAT_H
