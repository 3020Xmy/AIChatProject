#ifndef FRIENDLIST_MODEL_H
#define FRIENDLIST_MODEL_H

#include <QWidget>
#include <QToolBox>
#include <QListWidget>
#include "uiFile/FriendModel/FriendInfo.h"

class FriendList_Model : public QToolBox
{
    Q_OBJECT

public:
    ~FriendList_Model();
    explicit FriendList_Model(QWidget *parent = nullptr);

////------------------------------------界面模块函数-------------------------------------------------------------
public:
    //新增分组
    int handle_AddFriendList(const QString &groupname);
    //将好友插入分组
    int handle_FriendInsertlist(QSharedPointer<QListWidget> &List, QSharedPointer<FriendInfo> &Friend);
    //新增好友
    int handle_AddFriend(const QString &name, const QString &sign, const QString &number, const QString headimg,
                         const QString &state);
////------------------------------------信息发送模块函数-------------------------------------------------------------
public:
    //请求FriendInfo界面处理好友发送的图片
    int request_ImgToFriendInfo(const QString& sendind,const QString& ImgPath);
    //请求FriendInfo界面处理好友发送的信息
    int request_MessageToFriendInfo(const QString& sendind,const QString& message);
public slots:
    //转发至UserInfo界面处理发送的信息
    int handle_SendingMessageinUserInfo(const QString &friendnumber, const QString &message);
signals:
    //转发至UserInfo界面处理信息
    void relay_SendingMessageinUserInfo(const QString &friendnumber, const QString &message);
////------------------------------------表情发送模块函数-------------------------------------------------------------
public:
    //请求FriendInfo界面处理好友发送的表情
    int request_EmotionToFriendInfo(const QString& sendind,const QString& emotion);
public slots:
    //转发至UserInfo界面处理发送的表情
    int handle_SendingEmotioninUserInfo(const QString &friendnumber, const QString &emotion);
signals:
    //转发至UserInfo界面处理表情
    void relay_SendingEmotioninUserInfo(const QString &friendnumber, const QString &emotion);
////------------------------------------图片发送模块函数-------------------------------------------------------------
public slots:
    //转发至UserInfo界面处理发送的图片Json信息
    int handle_SendingImgJsoninUserInfo(const QJsonObject& sendingObj);
signals:
    //转发至UserInfo界面处理图片Json信息
    void relay_SendingImgJsoninUserInfo(const QString& receiveObj,const QJsonObject& sendingObj);
////------------------------------------文件发送模块函数-------------------------------------------------------------
public slots:
    //转发至UserInfo界面处理文件请求
    void handle_RelayFileRequestinUserInfo();
    //转发至UserInfo界面处理发送的文件路径
    int handle_FilePathinUserInfo(const QString& filePaht);
    //处理文件传输进度
    void handle_FileSchedule(const QString& Obj,qint64 size);
    //处理接收的文件接收进度
    void handle_ReceiveFileSchedule(const QString& Obj,qint64 size);
    //将文件信息转发至聊天界面显示
    void handle_RelayFileInfoinChat(const QString& sendingObj, const QJsonObject& jsonObject);
    //转发至UserInfo界面处理发送的文件Json信息
    int handle_SendingFileJsoninUserInfo(const QString& receiveFileObj, const QJsonObject& sendingObj);
signals:
    //转发至UserInfo界面处理文件请求
    void relay_FileRequestinUserInfo();
    //转发至UserInfo界面处理发送的文件路径
    void relay_FilePathinUserInfo(const QString& filePaht);
    //转发至UserInfo界面处理文件Json信息
    void relay_SendingFileJsoninUserInfo(const QString& receiveFileObj, const QJsonObject& sendingObj);

private:
    int len;    //好友个数
    QVector<QSharedPointer<FriendInfo>> FriendInfo_Vector;          //好友信息框容器
    QVector<QSharedPointer<QListWidget>> ListWidget_Vector;         //分组信息框容器

};

#endif // FRIENDLIST_MODEL_H
