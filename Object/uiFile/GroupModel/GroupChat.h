#ifndef GROUPCHAT_H
#define GROUPCHAT_H

#include <QFile>
#include <QWidget>
#include <QScrollBar>
#include <QMouseEvent>
#include "srcFile/USER.h"
#include <QListWidgetItem>
#include "uiFile/Chatbubble/Sendbox.h"
#include "uiFile/Chatbubble/Recvbox.h"

namespace Ui {
class GroupChat;
}

class GroupChat : public QWidget
{
    Q_OBJECT

public:
    ~GroupChat();
    explicit GroupChat(QWidget *parent = nullptr);
    explicit GroupChat(const QString &name, const QString &id,
                       const QString &head_Path, QWidget *parent = nullptr);

////------------------------------------事件模块函数-------------------------------------------------------------
protected:
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
////------------------------------------界面模块函数-------------------------------------------------------------
public:
    //获取群聊ID
    QString get_GroupNumber();
    //将发送的信息打包为Json
    QJsonObject handle_SendingDataPackageAsJSON();
    //处理项更新
    int handle_NewChatItem(QListWidgetItem *item, ChatBox* box);
    //处理接收的群聊消息
    int handle_GroupMessage(const QString& message,const QString& img);
    //初始化群聊界面
    int init_GroupChatWidget(const QString &name, const QString &id, const QString &head_Path);
private slots:
    //Top关闭界面函数
    void on_close_Btn_clicked();
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //发送按钮
    void on_sending_Btn_clicked();
    //Bottom关闭界面函数
    void on_close_Btnbottom_clicked();
signals:
    //请求发送消息
    void handle_SendingGroupMessage(const QJsonObject& sendingObj);

private:
    Ui::GroupChat *ui;
    bool move_Ok;   //是否移动
    QPoint move_point;  //移动的距离
    QString group_id;      //群聊ID
    QString group_name;    //群聊昵称
    QString group_headimg; //群聊头像
};

#endif // GROUPCHAT_H
