#ifndef FRIENDINFO_H
#define FRIENDINFO_H

#include <QPixmap>
#include <QToolBox>
#include <QMouseEvent>
#include <QStackedLayout>
#include "uiFile/FriendModel/FriendChat.h"

class FriendChat;

namespace Ui {
class FriendInfo;
}

class FriendInfo : public QWidget
{
    Q_OBJECT
public:
    ~FriendInfo();
    explicit FriendInfo(QWidget *parent = nullptr);
    explicit FriendInfo(const QString &name, const QString &sign, const QString &number,
                        const QString headimg, const QString &state, QWidget *parent = nullptr);

////------------------------------------界面处理模块函数-------------------------------------------------------------
public:
    //初始化界面
    int handle_FriendInfoinitWidget(const QString &name, const QString &sign, const QString &number,
                                   const QString headimg,const QString &state);
protected:
    //双击好友显示对话框
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
////------------------------------------信息发送模块函数-------------------------------------------------------------
public:
    //请求FriendChat界面处理好友信息
    int request_MessageToFriendChat(const QString& sendind,const QString& message);
public slots:
    //处理转发的消息
    int handle_RelaySengingMessage(const QString &friendnumber, const QString &message);
signals:
    //转发至FriendList_Model处理发送的消息
    void relay_SendingMessageinModel(const QString &friendnumber, const QString &message);
////------------------------------------表情发送模块函数-------------------------------------------------------------
public:
    //请求FriendChat界面处理好友表情
    int request_EmotionToFriendChat(const QString& sendind,const QString& emotion);
public slots:
    //处理转发的表情
    int handle_RelaySengingEmotion(const QString &friendnumber, const QString &emotion);
signals:
    //转发至FriendList_Model处理发送的表情
    void relay_SendingEmotioninModel(const QString &friendnumber, const QString &emotion);
////------------------------------------图片发送模块函数-------------------------------------------------------------
public:
    //请求FriendChat界面处理好友图片
    int request_ImgToFriendChat(const QString& sendind,const QString& ImgPath);
public slots:
    //处理转发的图片Json消息
    int handle_RelaySengingImgJson(const QJsonObject& sendingObj);
signals:
    //转发至FriendList_Model处理发送的图片Json信息
    void relay_SendingImgJsoninModel(const QJsonObject& sendingObj);
////------------------------------------文件发送模块函数-------------------------------------------------------------
public:
    //处理转发发送的文件进度
    int relay_FileSchedule(const QString& Obj,qint64 size);
    //处理转发接收的文件进度
    int relay_ReceiveFileSchedule(const QString& Obj,qint64 size);
    //处理好友发送的的文件信息
    int handle_FileInfo(const QString& receiveFileObj, const QJsonObject& sendingObj);
public slots:
    //转发至FriendList_Model处理文件请求
    int handle_RelayFileRequest();
    //处理转发的文件
    int relay_SendingFile(const QString &filepath);
    //处理转发的文件Json消息
    int handle_RelaySengingFileJson(const QString& receiveFileObj, const QJsonObject& sendingObj);
signals:
    //转发至FriendList_Model处理文件请求
    void handle_RelayFileRequestinModel();
    //转发至FriendList_Model处理发送的文件
    void relay_FilePathinFriendModel(const QString &filepath);
    //转发至FriendList_Model处理发送的文件Json信息
    void relay_SendingFileJsoninModel(const QString& receiveFileObj, const QJsonObject& sendingObj);

private:
    Ui::FriendInfo *ui;
    QSharedPointer<FriendChat> Chat;

};

#endif // FRIENDINFO_H
