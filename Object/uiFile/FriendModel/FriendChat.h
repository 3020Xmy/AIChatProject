#ifndef FRIENDCHAT_H
#define FRIENDCHAT_H

#include <QFile>
#include <QWidget>
#include <QLayout>
#include <QScrollBar>
#include <QThreadPool>
#include <QFileDialog>
#include <QMouseEvent>
#include "srcFile/USER.h"
#include <QListWidgetItem>
#include "uiFile/Emotion/Emotion.h"
#include "uiFile/Chatbubble/Sendbox.h"
#include "uiFile/Chatbubble/Recvbox.h"
#include "uiFile/Chatbubble/recvFilebox.h"
#include "uiFile/Chatbubble/sendFilebox.h"

namespace Ui {
class FriendChat;
}

class FriendChat : public QWidget
{
    Q_OBJECT

public:
    ~FriendChat();
    explicit FriendChat(QWidget *parent = nullptr);
    explicit FriendChat(const QString &name, const QString &sign,
                        const QString &number, const QString headimg,
                        const QString &state, QWidget *parent = nullptr);

////------------------------------------事件模块函数-------------------------------------------------------------
protected:
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //事件过滤器
    virtual bool eventFilter(QObject *watched, QEvent *event) override;
////------------------------------------界面模块函数-------------------------------------------------------------
public:
    //获取好友账号
    QString get_FriendNumber();
    //初始化好友聊天界面
    int init_FriendChatWidget();
    //处理输入框显示图片
    int handle_TextEditShowImg(const QString& path);
    //处理项更新
    int handle_NewItem(QListWidgetItem *item, ChatBox* box);
    //修改好友信息
    int set_FriendInfo(const QString &headPath,const QString &name,const QString &sign);
private slots:
    //选择传输文件函数
    void on_file_Btn_clicked();
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //发送按钮
    void on_sending_Btn_clicked();
    //Top关闭界面函数
    void on_close_Btntop_clicked();
    //Bottom关闭界面函数
    void on_close_Btnbottom_clicked();
////------------------------------------表情发送模块函数-------------------------------------------------------------
public:
    //处理接收的好友表情
    int handle_FriendEmotion(const QString &emotion);
    //处理用户发送的表情
    int handle_UserSendingEmotion(const QString &imgpath);
signals:
    //请求发送消息
    void handle_SendingEmotion(const QString& sendingObj,const QString &imgpath);
////------------------------------------信息发送模块函数-------------------------------------------------------------
public:
    //处理用户发送的信息
    int handle_UserSendingMessage();
    //处理好友信息
    int handle_FriendMessage(const QString &message);
signals:
    //请求发送消息
    void handle_SendingMessage(const QString& sendingObj,const QString &message);
////------------------------------------图片发送模块函数-------------------------------------------------------------
public:
    //处理用户发送的图片
    int handle_UserSendingImg();
    //处理好友发送的图片
    int handle_FriendImg(const QString &img);
    //将发送的图片信息打包为Json格式
    QJsonObject handle_ImgPackageAsJSON(const QString &imgpath);
private slots:
    //选择图片函数
    void on_img_Btn_clicked();
signals:
    //请求发送图片Json信息
    void handle_SendingImgInfoJson(const QJsonObject& sendingObj);
////------------------------------------文件发送模块函数-------------------------------------------------------------
public:
    //处理用户发送的文件
    int handle_UserSendingFile();
    //转发发送文件请求至FriendInfo
    int handle_ForwardSendingFileRequest();
    //处理用户发送的文件进度
    int handle_SendingFileSchedule(qint64 size);
    //处理接收的文件进度
    int handle_ReceiveFileSchedule(qint64 size);
    //显示好友发送的文件气泡
    int handle_ShowFileBox(const QJsonObject &jsonObject);
    //将发送的文件信息打包为Json格式
    QJsonObject handle_FilePackageAsJSON(const QString& Path);
    //将发送的文件信息打包为Json格式
    QJsonObject handle_FileInfoPackageAsJSON(const QString& path);
signals:
    //转发请求文件
    void handle_ForwardFileRequest();
    //请求发送的文件路径
    void handle_SendingFilePath(const QString & path);
    //请求发送文件Json信息
    void handle_SendingFileInfoJson(const QString& receiveFileObj, const QJsonObject& sendingObj);

private:
    Ui::FriendChat *ui;
    QString type;       //当前操作
    bool move_Ok;       //是否移动
    QString filePath;   //发送的文件路径
    Emotion* emotion;   //表情包对象
    QPoint move_point;  //移动的距离
    sendFilebox* send_File;       //文件发送气泡
    recvFilebox* recv_File;       //文件接收气泡

private:
    QString friend_name;    //好友昵称
    QString friend_sign;    //好友个签
    QString friend_state;   //好友状态
    QString friend_number;  //好友账号
    QString friend_headimg; //好友头像
};

#endif // FRIENDCHAT_H
