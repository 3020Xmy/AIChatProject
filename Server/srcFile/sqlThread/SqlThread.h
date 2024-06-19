#ifndef SQLTHREAD_H
#define SQLTHREAD_H

#include <QtSql>
#include <QMutex>
#include <QObject>
#include <QSqlError>
#include <QRunnable>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QMutexLocker>

class SqlThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ~SqlThread();
    //线程执行函数
    virtual void run() override;
    explicit SqlThread(QObject *parent = nullptr);
    explicit SqlThread(const QString &type,const QString &query,QObject *parent = nullptr);

////-------------------------------------------用户退出模块函数---------------------------------------------------
public slots:
    int handle_NewUserStateinExit(const QString& sqlcode);
////-------------------------------------------Sql模块函数-------------------------------------------------------
public:
    //初始化数据库线程
    int init_SqlThread();
public slots:
    //处理关闭数据库线程操作
    int handle_SQLDisconnect();
////-------------------------------------------登录模块函数-------------------------------------------------------
public:
    //查找用户群组信息
    int selete_UserinGroupinfo(QJsonObject &groupjson, const QString &number);
    //查找用户好友信息
    int selete_UserinFreindinfo(QJsonObject &friendjson, const QString &number);
public slots:
    //处理登录请求验证用户数据
    int handle_LoginVerifyUserData(const QString &id, const QString &query);
signals:
    //返回用户登录验证信息结果
    void return_LoginVerifyUserResult(const QString &id, const QJsonObject& rootObj);
////--------------------------------------------加密模块函数-----------------------------------------------------
public slots:
    //处理添加用户加密数据操作
    int handle_AddEncryptData(const QString &id, const QString &query);
signals:
    //返回添加用户加密数据操作结果
    void return_AddEncryptResult(const QString &id, const QJsonObject& rootObj);
////--------------------------------------------Ai模块函数-----------------------------------------------------
public:
    //将Ai信息结果封装成Json
    int handle_AiInfoPackageAsJSON(QJsonObject& rootObj, const QString& code,
                                   const QString& result, const QString &type);
public slots:
    //设置Ai信息
    int handle_SetAiInfo(const QString &id, const QString &query);
    //获取Ai信息
    int handle_GetAiInfo(const QString &id, const QString &query);
signals:
    //返回数据库设置Ai信息结果
    void return_SetAiResult(const QString &id,const QJsonObject& rootObj);
    //返回数据库查询Ai信息操作结果
    void return_GetAiOperateResult(const QString &id, const QJsonObject& rootObj);
////--------------------------------------------注册模块函数-----------------------------------------------------
public slots:
    //处理注册用户操作
    int handle_RegisterUserResult(const QString &id, const QString &query);
signals:
    //返回数据库查询信息操作结果
    void return_SeleteResult(const QString &id, const QString &result);
    //返回用户注册操作结果
    void return_UserRegisterResult(const QString &id, const QJsonObject& rootObj);

////--------------------------------------------添加好友模块函数-----------------------------------------------------
public:
    //将好友信息打包为Json
    int handle_FriendInfoPackageAsJSON(QJsonObject& rootObj, const QString &sqlcode);
public slots:
    //处理查询好友信息操作
    int handle_SeleteFriendInfo(const QString &id, const QString &sqldata);
    //处理申请好友验证操作
    int handle_AddFriendOperator(const QString &id, const QString &sqlcode);
    //处理添加好友链接数据
    int handle_AddFriendLinkData(const QString &id, const QString &friendnumber);
signals:
    //返回添加好友链接数据结果
    void return_AddFriendLinkDataResult(const QString &id, QJsonObject rootObj);
    //返回请求好友验证
    void return_ApplyForFriendVerifyResult(const QString &id,QJsonObject rootObj);
    //返回数据库查询好友信息操作结果
    void return_SeleteinFriendResult(const QString &id, const QJsonObject& rootObj);
////--------------------------------------------添加群聊模块函数-----------------------------------------------------
public:
    //将群聊信息打包为Json
    int handle_GroupInfoPackageAsJSON(QJsonObject& rootObj, const QString &sqlcode);
    //将链接群聊信息打包为Json
    int handle_GroupLinkDataPackageAsJSON(const QString &code, const QString &id, const QString &number);
public slots:
    //处理申请群聊验证操作
    int handle_AddGroupLinkData(const QString &id, const QString &number);
    //处理查询群聊信息操作
    int handle_SeleteGroupInfo(const QString &id, const QString &sqlcode);
signals:
    //返回数据库链接群聊操作结果
    void return_GroupLinkResult(const QString &id, const QJsonObject& rootObj);
    //返回数据库查询群聊信息操作结果
    void return_SeleteinGroupResult(const QString &id, const QJsonObject& rootObj);


private:
    QMutex mutex;  //互斥锁
    QSqlQuery *sql_Code;   //数据库查询语句
    bool SQLdiscon = false;//判断数据库是否断开连接
    QSqlDatabase *Data_Base;//数据库对象

};

#endif // SQLTHREAD_H
