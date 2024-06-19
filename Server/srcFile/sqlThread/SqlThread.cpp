#include "SqlThread.h"
#include <QDebug>

SqlThread::SqlThread(QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    //初始化数据库线程
    init_SqlThread();
}

/*  创建指定操作的线程
 *  type：操作类型   query：Sql语句
*/
SqlThread::SqlThread(const QString &type,const QString &query,QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    //初始化数据库线程
    init_SqlThread();
}

SqlThread::~SqlThread()
{
    delete Data_Base;
    delete sql_Code;
}

/*  线程执行函数
*/
void SqlThread::run()
{
    if (Data_Base->open()) {    //尝试连接数据库
        sql_Code = new QSqlQuery(*Data_Base);
    } else {
        QString Str =  QStringLiteral("连接数据库失败：%1").arg(Data_Base->lastError().text());
        QMessageBox::information(nullptr,"提示",Str,QMessageBox::Ok);
    }
    while(!SQLdiscon);
}

////---------------------------------------用户退出模块函数----------------------------------------------------------
/*  处理注册用户操作
 *  sqlcode：执行的Sql语句
*/
int SqlThread::handle_NewUserStateinExit(const QString &sqlcode)
{
    sql_Code->exec(sqlcode);
    return 1;
}

////---------------------------------------注册模块函数----------------------------------------------------------
/*  处理注册用户操作
 *  id：线程ID    query：执行的Sql语句
*/
int SqlThread::handle_RegisterUserResult(const QString &id, const QString &query)
{
    QJsonObject rootObj;     //返回客户端的Json对象
    if(sql_Code->exec(query)){     //注册用户成功
        rootObj.insert("type","register");
        rootObj.insert("code","21");
        rootObj.insert("return","True");
        rootObj.insert("userNumber",id);
        emit return_UserRegisterResult(id,rootObj);   //返回操作结果
        return 1;
    }
    else{   //注册用户失败
        rootObj.insert("type","register");
        rootObj.insert("code","20");
        rootObj.insert("return","False");
        rootObj.insert("userNumber",id);
        emit return_UserRegisterResult(id,rootObj);  //返回操作结果
        return 0;
    }
    return -1;
}

////---------------------------------------Ai模块函数----------------------------------------------------------
/*  设置Ai信息
 *  id：线程ID    query：执行的Sql语句
*/
int SqlThread::handle_SetAiInfo(const QString &id, const QString &query)
{
    if(sql_Code->exec(query)){     //执行设置Ai信息操作
        QJsonObject rootObj;    //传输的Json数据
        QString selete = QStringLiteral("SELECT * FROM aiinfo WHERE number = '%1';").arg(id);
        if(sql_Code->exec(selete) && sql_Code->next()){     //执行查询Ai信息操作
            handle_AiInfoPackageAsJSON(rootObj,"51","True","setAi");
            emit return_SetAiResult(id,rootObj);
            return 1;
        }
        else{
            handle_AiInfoPackageAsJSON(rootObj,"50","True","setAi");
            emit return_SetAiResult(id,rootObj);
            return 0;
        }
    }
    return -1;
}

/*  获取Ai信息
 *  id：线程ID    query：执行的Sql语句
*/
int SqlThread::handle_GetAiInfo(const QString &id, const QString &query)
{
    QJsonObject rootObj;    //传输的Json数据
    if(sql_Code->exec(query)){
        while(sql_Code->next()){     //开始查询
            if(sql_Code->record().count()){    //查询到Ai信息
                handle_AiInfoPackageAsJSON(rootObj,"41","True","getAi");
                emit return_GetAiOperateResult(id,rootObj);
                return 1;
            }
        }
    }
    handle_AiInfoPackageAsJSON(rootObj,"42","False","getAi");    //未查询到Ai信息
    emit return_GetAiOperateResult(id,rootObj);
    return 0;
}

/*  将Ai信息结果封装成Json
 *  rootObj：返回客户端的Json    code：信息码    result：操作结果    type：操作类型
*/
int SqlThread::handle_AiInfoPackageAsJSON(QJsonObject &rootObj, const QString &code,
                                          const QString &result, const QString &type)
{
    QJsonObject dataObj;
    rootObj.insert("type",type);
    rootObj.insert("return",result);
    rootObj.insert("code",code);
    dataObj.insert("userNumber",sql_Code->value("number").toString());
    dataObj.insert("APIkey",sql_Code->value("APIKey").toString());
    dataObj.insert("Aisign",sql_Code->value("sign").toString());
    dataObj.insert("Ainame",sql_Code->value("name").toString());
    dataObj.insert("APIsecret",sql_Code->value("APIsecret").toString());
    rootObj.insert("data",dataObj);
}

////---------------------------------------Sql模块函数----------------------------------------------------------
/*  初始化数据库线程
*/
int SqlThread::init_SqlThread()
{
    setAutoDelete(true);    //设置线程自动析构

    //配置数据库信息
    Data_Base = new QSqlDatabase();
    *Data_Base = QSqlDatabase::addDatabase("QMYSQL");
    Data_Base->setHostName("127.0.0.1");
    Data_Base->setPort(3306);
    Data_Base->setUserName("root");
    Data_Base->setPassword("188197");
    Data_Base->setDatabaseName("qqdate");
}

/*  初始化数据库线程
*/
int SqlThread::handle_SQLDisconnect()
{
    SQLdiscon = true;
    return 1;
}

////---------------------------------------加密模块函数----------------------------------------------------------
/*  处理添加用户加密数据操作
 *  id：线程ID    query：执行的Sql语句
*/
int SqlThread::handle_AddEncryptData(const QString &id, const QString &query)
{
    QMutexLocker locker(&mutex);
    QJsonObject rootObj;    //传输的Json对象
    if(sql_Code->exec(query)){
        //加密数据添加成功
        rootObj.insert("type","encrypt");
        rootObj.insert("code","31");
        rootObj.insert("return","True");

        emit return_AddEncryptResult(id,rootObj); //返回操作结果
        return 1;
    }
    else{
        //加密数据添加失败
        rootObj.insert("type","encrypt");
        rootObj.insert("code","31");
        rootObj.insert("return","True");

        emit return_AddEncryptResult(id,rootObj); //返回操作结果
        return 0;
    }
    return -1;  //添加数据异常
}

////---------------------------------------登录模块函数----------------------------------------------------------
/*  处理登录请求验证用户数据
 *  id：线程ID    query：执行的Sql语句
*/
int SqlThread::handle_LoginVerifyUserData(const QString &id, const QString &query)
{
    QMutexLocker locker(&mutex);

    QJsonObject rootObj;    //登录结果Json对象
    if(sql_Code->exec(query)){
        rootObj.insert("type","login");
        if(sql_Code->next()){
            QJsonObject dataObj;    //初始化用户信息Json对象
            QJsonObject groupObj;   //初始化群聊信息Json对象
            QJsonObject friendObj;  //初始化好友信息Json对象
            dataObj.insert("userSex",sql_Code->value("sex").toString());
            dataObj.insert("userSign",sql_Code->value("sign").toString());
            dataObj.insert("userName",sql_Code->value("name").toString());
            dataObj.insert("userNumber",sql_Code->value("number").toString());
            dataObj.insert("userHeadimg",sql_Code->value("headimg_Path").toString());
            rootObj.insert("data",dataObj);

            if(sql_Code->value("state").toString() == "0"){
                selete_UserinGroupinfo(groupObj,id);     //查找用户群聊
                selete_UserinFreindinfo(friendObj,id);   //查找用户好友
                rootObj.insert("groupinfo",groupObj);
                rootObj.insert("friendinfo",friendObj);
                QString update = QStringLiteral("UPDATE user SET state = '1' WHERE number = '%1'")
                                     .arg(id);
                sql_Code->exec(update);    //更新用户状态

                rootObj.insert("code","1");
                rootObj.insert("return","True");
                emit return_LoginVerifyUserResult(id,rootObj);
                return 1;
            }
            else if(sql_Code->value("state").toString() == "1"){   //查找到用户，但用户已登录
                rootObj.insert("code","0");
                rootObj.insert("return","True");
                emit return_LoginVerifyUserResult(id,rootObj);
                return 0;
            }
        }
        else{   //用户信息异常
            rootObj.insert("code","2");
            rootObj.insert("return","False");
            emit return_LoginVerifyUserResult(id,rootObj);
            return -1;
        }
    }
}

/*  查找用户好友信息
 *  friendjson：接收好友信息的json对象    number：用户账号
*/
int SqlThread::selete_UserinFreindinfo(QJsonObject &friendjson, const QString &number)
{
    int len = 0;    //记录好友个数
    QString seleteFriend = QStringLiteral("SELECT * FROM user WHERE number IN ("
                                    "SELECT user_id FROM friend WHERE friend_id = '%1');")
                                    .arg(number);       //查找好友
    sql_Code->exec(seleteFriend);
    while (sql_Code->next()) {
        QJsonObject Obj;     //初始化Json对象
        Obj.insert("name",sql_Code->value(0).toString());
        Obj.insert("sign",sql_Code->value(4).toString());
        Obj.insert("state",sql_Code->value(7).toString());
        Obj.insert("number",sql_Code->value(1).toString());
        Obj.insert("headimg",sql_Code->value(5).toString());

        len+=1;  //好友个数+1
        QString friendref =  QStringLiteral("friend%1").arg(len);   //好友编号
        friendjson.insert(friendref,Obj);
    }
    friendjson.insert("friendLen",len);
    return 1;
}

/*  查找用户群聊信息
 *  groupjson：接收群聊数据的json对象    number：用户账号
*/
int SqlThread::selete_UserinGroupinfo(QJsonObject &groupjson, const QString &number)
{
    int len = 0;    //记录群聊个数
    //查找用户群聊
    QString seleteGroup = QStringLiteral("SELECT * FROM groupinfo WHERE group_id IN ("
                                    "SELECT group_id FROM groupuserinfo WHERE user_id = '%1');").arg(number);
    sql_Code->exec(seleteGroup);
    while (sql_Code->next()) {
        QJsonObject Obj;     //初始化Json对象
        Obj.insert("id",sql_Code->value(0).toString());
        Obj.insert("name",sql_Code->value(1).toString());
        Obj.insert("headimg",sql_Code->value(2).toString());

        len+=1;  //群聊个数+1
        QString groupref = QStringLiteral("group%1").arg(len);   //群聊编号
        groupjson.insert(groupref,Obj);
    }
    groupjson.insert("groupLen",len);
    return 1;
}

////---------------------------------------添加好友模块函数----------------------------------------------------------
/*  处理查询好友信息操作
 *  id：线程Id    sqlcode：执行的Sql语句
*/
int SqlThread::handle_SeleteFriendInfo(const QString &id, const QString &sqlcode)
{
    QJsonObject rootObj,data;    //返回值的Json数据
    rootObj.insert("type","selectFriend");
    if(handle_FriendInfoPackageAsJSON(data, sqlcode)){   //存在该用户
        rootObj.insert("data",data);
        rootObj.insert("code","61");
        rootObj.insert("return","True");
        emit return_SeleteinFriendResult(id,rootObj);   //请求返回查询到的好友信息
        return 1;
    }else{   //不存在该群聊
        rootObj.insert("code","62");
        rootObj.insert("return","False");
        emit return_SeleteinFriendResult(id,rootObj);
        return 0;
    }
}

/*  处理申请好友验证操作
 *  id：线程Id    sqlcode：执行的Sql语句
*/
int SqlThread::handle_AddFriendOperator(const QString &id, const QString &sqlcode)
{
    QJsonObject rootObj,data;    //返回值的Json数据
    if(handle_FriendInfoPackageAsJSON(data, sqlcode)){
        rootObj.insert("data",data);
        rootObj.insert("code","68");
        rootObj.insert("return","True");
        rootObj.insert("type","friendVerify");
        emit return_ApplyForFriendVerifyResult(id,rootObj);   //请求好友验证
        return 1;
    }
    return 0;
}

/*  处理申请好友验证操作
 *  id：线程Id    friendnumber：好友账号
*/
int SqlThread::handle_AddFriendLinkData(const QString &id, const QString &friendnumber)
{
    QJsonObject data1,data2,rootObj;         //返回值的Json数据
    rootObj.insert("type","return_AddFriendLinkResult");
    QString  Sql_Code1 = " ",Sql_Code2 = " ";//初始化执行的SQL语句
    Sql_Code1 = QStringLiteral("INSERT INTO friend (friend_id, user_id) VALUES"
                                      "('%1','%2'),"
                                      "('%3','%4');").arg(id).arg(friendnumber).arg(friendnumber).arg(id);
    if(sql_Code->exec(Sql_Code1)){   //添加成功
        Sql_Code1 = QStringLiteral("SELECT * FROM user WHERE number = '%1'").arg(id);
        Sql_Code2 = QStringLiteral("SELECT * FROM user WHERE number = '%1'").arg(friendnumber);
        if(handle_FriendInfoPackageAsJSON(data1,Sql_Code1) &&
           handle_FriendInfoPackageAsJSON(data2,Sql_Code2)){
            rootObj.insert("code","65");
            //插入链接的用户信息
            rootObj.insert("data1",data1);
            rootObj.insert("data2",data2);
        }else{
            rootObj.insert("code","62");
        }
        rootObj.insert("return","True");
    }
    else{
        //添加失败
        rootObj.insert("code","67");
        rootObj.insert("return","False");
        emit return_AddFriendLinkDataResult(friendnumber,rootObj);
        return 0;
    }
    rootObj.insert("type","return_AddFriendLinkResult");
    emit return_AddFriendLinkDataResult(id,rootObj);
    emit return_AddFriendLinkDataResult(friendnumber,rootObj);
    return 1;
}

/*  处理申请好友验证操作
 *  data：打包的Json对象    sqlcode：执行的SQL语句
*/
int SqlThread::handle_FriendInfoPackageAsJSON(QJsonObject& data, const QString &sqlcode)
{
    if(sql_Code->exec(sqlcode)){
        sql_Code->next();
        if(sql_Code->value("number").toString().isEmpty()){
            return 0;
        }else{
            data.insert("friendsex",sql_Code->value("sex").toString());
            data.insert("friendsign",sql_Code->value("sign").toString());
            data.insert("friendname",sql_Code->value("name").toString());
            data.insert("friendstate",sql_Code->value("state").toString());
            data.insert("friendnumber",sql_Code->value("number").toString());
            data.insert("friendheadimg",sql_Code->value("headimg_Path").toString());
        }
        return 1;
    }
    return 0;
}

////---------------------------------------添加群聊模块函数----------------------------------------------------------
/*  处理查询群聊信息操作
 *  id：线程Id    sqlcode：执行的Sql语句
*/
int SqlThread::handle_SeleteGroupInfo(const QString &id, const QString &sqlcode)
{
    QJsonObject rootObj,data;    //返回值的Json数据
    rootObj.insert("type","selectGroup");
    if(handle_GroupInfoPackageAsJSON(data, sqlcode)){   //存在该群聊
        rootObj.insert("data",data);
        rootObj.insert("code","91");
        rootObj.insert("return","True");
        emit return_SeleteinGroupResult(id,rootObj);   //请求返回查询到的好友信息
        return 1;
    }else{   //不存在该群聊
        rootObj.insert("code","92");
        rootObj.insert("return","False");
        emit return_SeleteinFriendResult(id,rootObj);
        return 0;
    }
}

/*  将群聊信息打包为Json
 *  rootObj：打包的Json对象    sqlcode：执行的SQL语句
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int SqlThread::handle_GroupInfoPackageAsJSON(QJsonObject& data, const QString &sqlcode)
{
    if(sql_Code->exec(sqlcode)){
        sql_Code->next();
        if(sql_Code->value("group_id").toString().isEmpty()){
            return 0;
        }else{
            data.insert("groupname",sql_Code->value("group_name").toString());
            data.insert("groupnumber",sql_Code->value("group_id").toString());
            data.insert("groupheadimg",sql_Code->value("group_headimg").toString());
            return 1;
        }
    }
}

/*  处理申请群聊验证操作
 *  id：线程Id    number：添加的群聊号码
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int SqlThread::handle_AddGroupLinkData(const QString &id, const QString &number)
{
    QString Sql_Code = QStringLiteral("SELECT * FROM groupuserinfo WHERE group_id = '%1' AND user_id = '%1';")
                           .arg(number).arg(id);
    if(sql_Code->exec(Sql_Code)){
        sql_Code->next();
        if(sql_Code->value("user_id").toString().isEmpty()){
            Sql_Code = QStringLiteral("INSERT INTO groupuserinfo (group_id, user_id) VALUES"
                        "('%1','%2');").arg(number).arg(id);
            if(sql_Code->exec(Sql_Code)){
                handle_GroupLinkDataPackageAsJSON("93",id,number);
                return 1;
            }
        }
    }
    handle_GroupLinkDataPackageAsJSON("94",id,number);
    return 0;
}

/*  将链接群聊信息打包为Json
 *  code：信息码    id：用户ID    number：群聊号码
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int SqlThread::handle_GroupLinkDataPackageAsJSON(const QString &code, const QString &id, const QString &number)
{
    QJsonObject rootObj,data;    //返回的Json数据
    rootObj.insert("type","return_AddGroupLinkResult");
    QString Sql_Code = QStringLiteral("SELECT * FROM groupinfo WHERE group_id = '%1';").arg(number);
    if(sql_Code->exec(Sql_Code)){
        sql_Code->next();
        data.insert("groupname",sql_Code->value("group_name").toString());
        data.insert("groupnumber",sql_Code->value("group_id").toString());
        data.insert("groupheadimg",sql_Code->value("group_headimg").toString());
    }
    rootObj.insert("code",code);
    rootObj.insert("data",data);
    emit return_GroupLinkResult(id,rootObj);
}
