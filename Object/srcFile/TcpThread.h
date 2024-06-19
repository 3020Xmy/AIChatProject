#ifndef TcpThread_H
#define TcpThread_H

#include <QDir>
#include <QFile>
#include <QObject>
#include <QRunnable>
#include <QTcpSocket>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

class TcpThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ~TcpThread();
    virtual void run() override;
    explicit TcpThread(QObject *parent = nullptr);
    int handle_CloseThread(const QString& number);    //关闭线程
    explicit TcpThread(QTcpSocket *socket, QObject *parent = nullptr);
////-----------------------------------处理文件模块函数----------------------------------------------------------
public:
    //返回服务器同意接受文件Json
    int handle_FileStateAsJson();
    //设置发送的文件大小
    int handle_SetSendingFileSize(qint64 value);
    //接收文件数据
    int handle_ReceiveFileData(QByteArray filedata);
    //设置接收文件的好友
    int handle_SetReceiveFileObj(const QString &Obj);
    //发送文件至服务端
    int sending_FileToServer(const QString& filePath);
    //设置发送的文件类型
    int handle_SetSendingFileType(const QString& type);
    //处理要接受的文件信息Json
    int handle_ReceiveFileInfo(const QString& dir, const QJsonObject& jsonObject);
signals:
    //处理文件接收进度
    void handle_ShowReceiveFileSchedule(const QString& Obj, qint64 size);
    //处理文件传输进度
    void handle_ShowFileTransferSchedule(const QString& Obj, qint64 size);
    //处理文件信息至聊天界面显示
    void handle_ShowFileInfoinChat(const QString& sendingObj, const QJsonObject& jsonObject);
////-----------------------------------处理图片模块函数----------------------------------------------------------
signals:
    //转发至UserInfo界面处理好友图片
    void relay_FriendImgToUserInfo(const QString& sendind, const QString& imgpath);
////-----------------------------------处理表情模块函数----------------------------------------------------------
public:
    //处理好友表情
    int handle_FriendEmotionResult(const QJsonObject &jsonObject);
signals:
    //转发至UserInfo界面处理好友表情
    void relay_FriendEmotionToUserInfo(const QString& sendind, const QString& emotion);
////-----------------------------------处理信息模块函数----------------------------------------------------------
public:
    //处理群聊信息
    int handle_GroupMessingResult(const QJsonObject& jsonObject);
    //处理好友信息
    int handle_FriendMessingResult(const QJsonObject &jsonObject);
signals:
    //转发至UserInfo界面处理群聊信息
    void relay_GroupMessingToUserInfo(const QJsonObject& jsonObject);
    //转发至UserInfo界面处理好友信息
    void relay_FriendMessingToUserInfo(const QString& sendind, const QString& message);
////-----------------------------------Json模块函数----------------------------------------------------------
public:
    //处理服务端返回的Json
    int handle_ReturnJsonData(QByteArray jsondata);
////-----------------------------------Tcp模块函数-----------------------------------------------------------
public:
    //初始化Tcp链接
    int init_TcpConnect();
public slots:
    //服务器链接断开
    int handle_DisConnected();
    //接收服务器发送的信息
    void receive_ServerMessage();
    //连接服务器成功
    int handle_ConnectedSuccess();
    //发送消息至服务器
    int sending_ToServer(const QByteArray &jsondata);
////-----------------------------------登录模块函数-----------------------------------------------------------
public:
    //处理登录返回的信息
    int handle_LoginReturnUserInfo(const QJsonObject &jsonObject);
    //处理登录返回的群聊信息
    int handle_LoginReturnGroupInfo(const QJsonObject &groupinfo);
    //处理登录返回的好友信息
    int handle_LoginReturnFriendInfo(const QJsonObject &friendinfo);
signals:
    //登录操作获取的群聊信息返回给Login界面处理
    void return_GroupInfo(const QString &name, const QString &id, const QString headimg);
    //登录操作获取的好友信息返回给Login界面处理
    void return_FriendInfo(const QString &name, const QString &sign, const QString &number,
                           const QString headimg, const QString &state);
    //登录操作获取的用户信息返回给Login界面处理
    void return_UserInfo(bool ok, const QString &code, const QString &sex, const QString &name,
                         const QString &sign, const QString &number, const QString headimg);
////-----------------------------------注册模块函数-----------------------------------------------------------
public:
    //处理用户注册请求返回的信息
    int handle_UserRegisterResult(const QJsonObject &jsonObject);
signals:
    //注册用户请求结果返回给UserInfo界面处理
    void return_RegisterResult(bool ok);
////-----------------------------------加密模块函数-----------------------------------------------------------
public:
    //处理保存加密请求返回的信息
    int handle_EncryptResult(const QJsonObject &jsonObject);
signals:
    //保存加密信息请求的结果返回给UserInfo界面处理
    void return_SaveEncryptResult(const bool &ok,const QString &code);
////-----------------------------------AI模块函数-----------------------------------------------------------
public:
    //处理获取Ai（设置Ai）请求返回的信息
    int handle_AiResult(const QJsonObject &jsonObject);
signals:
    //添加AI结果返回给UserInfo界面处理
    void return_SetAiResult(bool ok, const QString &ai_Name,const QString &ai_Sign,
                            const QString &ai_ApiKey,const QString &ai_ApiSecret);
    //获取AI结果返回给UserInfo界面处理
    void return_GetAiResult(bool ok,const QString &ai_Name,const QString &ai_Sign,
                             const QString &ai_ApiKey,const QString &ai_ApiSecret);
////-----------------------------------添加好友模块函数------------------------------------------------------
public:
    //处理好友验证的请求的信息
    int handle_FriendVerify(const QJsonObject &jsonObject);
    //处理查询好友信息操作返回的信息
    int handle_SeleteFriendInfo(const QJsonObject &jsonObject);
signals:
    //转发至UserInfo界面处理新增好友链接结果
    void relay_AddFriendLinkResult(const QJsonObject &jsondata);
    //将好友验证请求转发给UserInfo界面处理
    void return_FriendVerify(const QString &name, const QString &sex, const QString &sign,
                             const QString &number, const QString &headimg_Path);
    //服务器获取的好友信息转发给UserInfo界面处理
    void return_AddFriendInfo(const QString& code,  const QString &state,const QString &name, const QString &sex,
                              const QString &sign, const QString &number, const QString &headimg_Path);
////-----------------------------------添加群组模块函数------------------------------------------------------
public:
    //处理查询好友信息操作返回的信息
    int handle_SeleteGroupInfo(const QJsonObject &jsonObject);
signals:
    //转发至UserInfo界面处理新增群聊链接结果
    void relay_AddGroupLinkResult(const QJsonObject &jsondata);
    //服务器获取的群聊信息转发给UserInfo界面处理
    void return_AddGroupInfo(const QString& code, const QString &number, const QString &name,
                             const QString &headimg_Path);

private:
    bool ok;    //线程状态
    QFile file; //文件对象
    qint64 file_Size;   //文件大小
    QString file_Type;  //文件类型
    QString file_Name;  //文件名称
    QString file_Path;  //文件保存路径
    bool isdisconnect;  //连接服务器状态
    QString read_Type;  //读取的操作类型
    qint64 sendingSize; //当前发送文件大小
    qint64 receiveSize; //当前接收文件大小
    QString sendingType;//发送的文件类型
    QString sendingFileObj; //发送文件的好友
    QString receiveFileObj; //接收文件的好友
    QTcpSocket *server_DataService = nullptr;   //通信对象
};

#endif // TcpThread_H
