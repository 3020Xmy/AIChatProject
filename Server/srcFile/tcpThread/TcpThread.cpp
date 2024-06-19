#include "TcpThread.h"
#include <QDebug>

TcpThread::TcpThread(QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    setAutoDelete(true);//设置线程自动析构
}

TcpThread::TcpThread(QTcpSocket *socket, int value, QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    //初始化对象
    file_Size = 0;
    recvedSize = 0;
    file_Name = " ";
    file_Type = " ";
    file_State = true;
    ReceiveFileObj = " ";
    tcpThread_UserID = " ";
    tcpthread_UserPort = " ";
    Tcpthread_number = value;
    Tcpthread_Socket = socket;

    init_TcpConnect();  //初始化Tcp链接
    setAutoDelete(true);//设置线程自动析构
}

TcpThread::~TcpThread()
{

}

void TcpThread::run()
{
    handle_ClientConnected();//客户端成功连接
    while(!TCPdiscon);
}

/*  设置用户项Id
 *  port：线程端口    ItemId：用户项Id
*/
void TcpThread::handle_SetUserItemId(const QString &port, const int &ItemId)
{
    if(tcpthread_UserPort == port){
        userItem_Id = ItemId;
    }
}

////---------------------------------------文件模块函数----------------------------------------------------------
/*  处理好友发送文件Json操作
 *  dataObject：接收到的文件数据
*/
int TcpThread::handle_FriendSendingFile(QJsonObject dataObject)
{
    if(file_State){
        file_Type = "File";
        handle_FileSavePath(dataObject);
        return 1;
    }
}

/*  处理客户端发送的文件
 *  dataObject：接收到的文件数据
*/
void TcpThread::handle_SendingFile(QByteArray dataObject)
{
    file_State = false;
    qint64 len = file.write(dataObject); //将接收到的数据写入文件
    recvedSize += len;
    if(recvedSize == file_Size){
        file.close();
        recvedSize = 0;
        file_State = true;
        if(file_Type == "Img"){
            emit relay_FileJsonToMainWidget(ReceiveFileObj,file_Path,handle_FileJsonPackageAsJSON("friend_SendingImg",ReceiveFileObj));   //请求发送给好友
        }
        else if(file_Type == "File"){
            emit relay_FileJsonToMainWidget(ReceiveFileObj,file_Path,handle_FileJsonPackageAsJSON("friend_SendingFile",ReceiveFileObj));   //请求发送给好友
        }
        file_Type = " ";
    }
}

/*  处理客户端发送的文件保存路径
 *  dataObject：接收到的数据
*/
int TcpThread::handle_FileSavePath(QJsonObject dataObject)
{
    QDir().mkdir("files");     //设置保存的文件夹
    QJsonObject Object = dataObject["data"].toObject();
    ReceiveFileObj = Object["receiveObj"].toString();
    Object = dataObject["fileInfo"].toObject();
    file_Size = Object["fileSize"].toInt();
    file_Name = Object["fileName"].toString();
    file_Path = QDir::currentPath() + "/files/" + ReceiveFileObj + file_Name;
    file.setFileName(file_Path); //保存的路径
    file.open(QIODevice::WriteOnly);    //打开文件等待接收
}

/*  处理同意接收文件操作
 *  dataObject：接收到的数据
*/
void TcpThread::handle_FileStateisOk(QJsonObject dataObject)
{
    if(dataObject["data"].toString() == "Yes"){
        qint64 len = 0;
        qint64 sending = 0;
        file.setFileName(file_Path);
        if(!file.open(QIODevice::ReadOnly)){
            return;
        }
        do{
            char buf[4*1024];
            len = file.read(buf, sizeof(buf));
            len = Tcpthread_Socket->write(buf, len);
            sending += len;
            if(sending == file_Size){  //确保发送的字节数不超过文件大小
                file.close();
                break;
            }
        }while(len > 0);
    }
}

/*  转发至好友的文件Json数据
 *  type：文件类型    number：接收的账号
*/
QJsonObject TcpThread::handle_FileJsonPackageAsJSON(const QString& type,const QString& number)
{
    QJsonObject Json;
    Json.insert("type",type);
    QJsonObject dataObj;
    dataObj.insert("sendingObj",tcpThread_UserID);
    dataObj.insert("receiveObj",number);
    dataObj.insert("fileName",file_Name);
    dataObj.insert("fileSize",file_Size);
    Json.insert("data",dataObj);
    return Json;
}

/*  发送请求客户端接收文件信息
*/
void TcpThread::handle_RequestFileInfo(const QString &number, const QString &path, const QJsonObject &FileJson)
{
    file_Path = path;
    return_ClientData(number,FileJson);
}

////---------------------------------------图片发送模块函数----------------------------------------------------------
/*  处理好友发送图片Json操作
 *  dataObject：接收到的数据
*/
int TcpThread::handle_FriendSendingImg(QJsonObject dataObject)
{
    if(file_State){
        file_Type = "Img";
        QDir().mkdir("images");     //设置保存的文件夹
        handle_FileSavePath(dataObject);
        return 1;
    }
}

////---------------------------------------表情发送模块函数----------------------------------------------------------
/*  处理好友发送表情操作
 *  dataObject：接收到的数据
*/
int TcpThread::handle_FriendSendingEmotion(QJsonObject dataObject)
{
    emit relay_EmotionToMainWidget(dataObject["sendingObj"].toString(),dataObject["receiveObj"].toString(),
                                   dataObject["emotion"].toString());
    return 1;
}

////---------------------------------------消息发送模块函数----------------------------------------------------------
/*  处理好友发送消息操作
 *  dataObject：接收到的数据
*/
int TcpThread::handle_FriendSendingMessage(QJsonObject dataObject)
{
    emit relay_MessageToMainWidget(dataObject["sendingObj"].toString(),dataObject["receiveObj"].toString(),
                                   dataObject["message"].toString());
    return 1;
}

/*  处理群聊发送消息操作
 *  dataObject：接收到的数据
*/
void TcpThread::handle_GroupSendingMessage(QJsonObject dataObject)
{
    QJsonObject Json;
    Json.insert("data",dataObject);
    Json.insert("type","receive_GroupMessage");
    emit relay_GroupMessageToMainWidget(Json);
}

////---------------------------------------用户退出模块函数----------------------------------------------------------
/*  处理退出客户端操作
*/
int TcpThread::handle_ExitClient()
{
    QString Sql_Code = QStringLiteral("UPDATE user SET state = '0' WHERE number = '%1'")
                         .arg(tcpThread_UserID);
    emit request_SqlNewUserStateinExit(Sql_Code);    //请求数据库更新用户状态为离线
    return 1;
}

////---------------------------------------Tcp模块函数----------------------------------------------------------
/*  初始化Tcp链接
*/
int TcpThread::init_TcpConnect()
{
    //客户端断开连接
    connect(Tcpthread_Socket,&QAbstractSocket::disconnected,this,&TcpThread::handle_ClientDisconnected);
    //读取客户端发送的信息
    connect(Tcpthread_Socket,&QAbstractSocket::readyRead,this,&TcpThread::get_ClientSendingData);
    return 1;
}

/*  读取客户短消息
*/
int TcpThread::get_ClientSendingData()
{
    execute_JsonOperate(Tcpthread_Socket->readAll());
    return 1;
}

/*  返回信息至客户端
 *  id：线程ID    rootObj：返回客户端的Json
*/
int TcpThread::return_ClientData(const QString &id, QJsonObject rootObj)
{
    if(tcpThread_UserID == id){
        QJsonDocument jsonDocument(rootObj);
        QByteArray jsonData = jsonDocument.toJson();
        Tcpthread_Socket->write(jsonData);
        Tcpthread_Socket->flush();
        return 1;
    }
    return 0;
}

/*  客户端成功连接
*/
int TcpThread::handle_ClientConnected()
{
    tcpthread_UserPort = QString::number(Tcpthread_Socket->peerPort());
    if (Tcpthread_Socket->peerAddress().toString().startsWith("::ffff:")){
        emit request_NewUserConnect(Tcpthread_Socket->peerAddress().toString().mid(7),
                                    QString::number(Tcpthread_Socket->peerPort()));
    }
    else{
        emit request_NewUserConnect(Tcpthread_Socket->peerAddress().toString(),
                                    QString::number(Tcpthread_Socket->peerPort()));
    }
    return 1;
}

/*  客户端断开连接
*/
int TcpThread::handle_ClientDisconnected()
{
    handle_ExitClient();    //设置用户为离线状态
    Tcpthread_Socket->deleteLater();
    TCPdiscon = true;
    return 1;
}

/*  返回群聊消息至客户端
 *  rootObj：群聊消息
*/
int TcpThread::return_GroupinClien(QJsonObject rootObj)
{
    QJsonDocument jsonDocument(rootObj);
    QByteArray jsonData = jsonDocument.toJson();
    Tcpthread_Socket->write(jsonData);
    Tcpthread_Socket->flush();
}

/*  执行Json中的操作
*/
void TcpThread::execute_JsonOperate(QByteArray data_Array)
{
    //解析Json
    QJsonDocument jsonDocument = QJsonDocument::fromJson(data_Array);
    QJsonObject jsonObject = jsonDocument.object();
    QJsonObject dataObject = jsonObject["data"].toObject();
    read_type = jsonObject["type"].toString();

    if(!ismark){    //认领线程
        tcpThread_UserID = dataObject["userNumber"].toString();  //标记线程ID
        emit request_NewUserNumber(userItem_Id,tcpThread_UserID);//更新用户账号信息
        ismark = true;
    }

    if(read_type == "encrypt"){
        //处理加密操作
        handle_EncryptRequest(dataObject);
    }
    else if(read_type == "login"){
        //处理登录操作
        handle_UserLoginRequest(dataObject);
    }
    else if(read_type == "getAI"){
        //处理获取Ai信息操作
        handle_GetAiInfoRequest(dataObject);
    }
    else if(read_type == "setAI"){
        //处理设置Ai信息操作
        handle_SetAiInfoRequest(dataObject);
    }
    else if(read_type == "register"){
        //处理注册操作
        handle_UserRegisterRequest(dataObject);
    }
    else if(read_type == "exitClient"){
        //处理退出客户端操作
        handle_ExitClient();
    }
    else if(read_type == "selectFriend"){
        //处理查找好友信息操作
        handle_SelectFriendInfo(dataObject);
    }
    else if(read_type == "selectGroup"){
        //处理查找群聊信息操作
        handle_SelectGroupInfo(dataObject);
    }
    else if(read_type == "applyForfriendVerify"){
        //处理请求好友验证操作
        handle_AddFriendVerify(dataObject);
    }
    else if(read_type == "applyForgroupVerify"){
        //处理请求群聊验证操作
        handle_AddGroupVerify(dataObject);
    }
    else if(read_type == "addfriendResult"){
        //处理好友验证结果操作
        handle_AddFriendResult(dataObject);
    }
    else if(read_type == "friend_SendingMessing"){
        //处理好友发送消息操作
        handle_FriendSendingMessage(dataObject);
    }
    else if(read_type == "Sending_GroupData"){
        //处理群聊发送消息操作
        handle_GroupSendingMessage(dataObject);
    }
    else if(read_type == "friend_SendingEmotion"){
        //处理好友发送表情操作
        handle_FriendSendingEmotion(dataObject);
    }
    else if(read_type == "friend_SendingImg"){
        //处理好友发送图片操作
        file_Type = "Img";
        handle_FriendSendingImg(jsonObject);
    }
    else if(read_type == "friend_SendingFile"){
        //处理好友发送文件操作
        file_Type = "File";
        handle_FriendSendingFile(jsonObject );
    }
    else if(read_type == "FileState"){
        //处理同意接收文件操作
        handle_FileStateisOk(jsonObject );
    }
    else{
        read_type = "sendingFile";
        //处理文件操作
        handle_SendingFile(data_Array);
    }

    emit request_NewUserOperator(userItem_Id,read_type);    //更新用户当前操作
}

/*  处理关闭客户端线程操作
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_TCPDisconnect()
{
    TCPdiscon = true;
    return 1;
}

////---------------------------------------添加好友模块函数----------------------------------------------------------
/*  处理请求好友验证操作
 *  dataObject：接收到的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_AddFriendVerify(QJsonObject dataObject)
{
    QString Sql_Code = QStringLiteral("SELECT * FROM user WHERE number = '%1';").arg(tcpThread_UserID);
    emit relay_AddFriendVerify(dataObject["friendNumber"].toString(),Sql_Code);
}

/*  处理好友验证结果操作
 *  dataObject：接收到的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_AddFriendResult(QJsonObject dataObject)
{
    emit request_AddFriendLinkData(tcpThread_UserID,dataObject["friendNumber"].toString());
}

/*  处理获取好友信息请求
 *  dataObject：接收到的数据
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int TcpThread::handle_SelectFriendInfo(QJsonObject dataObject)
{
    //查询是否存在该账号
    QString friend_Number = dataObject["friendNumber"].toString();
    QString Sql_Code = QStringLiteral("SELECT * FROM user WHERE number = '%1'").arg(friend_Number);
    emit request_SqlSeleteFriendInfo(tcpThread_UserID,Sql_Code);
    return 1;
}

////---------------------------------------添加群聊模块函数-----------------------------------------------------
/*  处理获取群聊信息请求
 *  dataObject：接收到的数据
*/
int TcpThread::handle_SelectGroupInfo(QJsonObject dataObject)
{
    //查询是否存在该账号
    QString group_Number = dataObject["groupNumber"].toString();
    QString Sql_Code = QStringLiteral("SELECT * FROM groupinfo WHERE group_id = '%1';").arg(group_Number);
    emit request_SqlSeleteGroupInfo(tcpThread_UserID,Sql_Code);
    return 1;
}

/*  处理请求群聊验证操作
 *  dataObject：接收到的数据
*/
int TcpThread::handle_AddGroupVerify(QJsonObject dataObject)
{
    emit request_AddGroupLinkData(tcpThread_UserID,dataObject["groupNumber"].toString());
}

////---------------------------------------Ai模块函数----------------------------------------------------------
/*  处理获取Ai信息请求
 *  dataObject：接收到的数据
*/
int TcpThread::handle_GetAiInfoRequest(QJsonObject dataObject)
{
    Q_UNUSED(dataObject);
    QString query = QStringLiteral("SELECT * FROM aiinfo WHERE number = '%1';").arg(tcpThread_UserID);
    emit request_SqlSeleteAiInfo(tcpThread_UserID,query);
}

/*  处理获取Ai信息请求
 *  dataObject：接收到的数据
*/
int TcpThread::handle_SetAiInfoRequest(QJsonObject dataObject)
{
    QString query =QStringLiteral("UPDATE aiinfo SET number = '%1', sign = '%2', name = '%3', APIKey = '%4', APISecret = '%5'"
                                   " WHERE number = '%6'")
                                    .arg(tcpThread_UserID)
                                    .arg(dataObject["Aisign"].toString())
                                    .arg(dataObject["Ainame"].toString())
                                    .arg(dataObject["APIkey"].toString())
                                    .arg(dataObject["APIsecret"].toString())
                                    .arg(tcpThread_UserID);
    emit request_SqlSetAiInfo(tcpThread_UserID,query);    //请求数据库设置Ai信息
    return 1;
}

////---------------------------------------加密模块函数----------------------------------------------------------
/*  处理客户端用户数据加密请求
 *  dataObject：接收到的数据
*/
int TcpThread::handle_EncryptRequest(QJsonObject dataObject)
{
    QString query = QStringLiteral("UPDATE user SET encrypt_Pswd = '%1' WHERE number = '%2';")
                    .arg(dataObject["userEncrypt"].toString()).arg(tcpThread_UserID);    //定义执行的Sql语句
    emit request_SaveEncryptData(tcpThread_UserID,query);  //请求数据库保存加密数据
    return 1;
}

////---------------------------------------注册模块函数----------------------------------------------------------
/*  处理用户注册请求
 *  dataObject：接收到的数据
*/
int TcpThread::handle_UserRegisterRequest(QJsonObject dataObject)
{

    QString query = QStringLiteral("INSERT INTO user (name, number, password, sex, sign, headimg_Path, encrypt_Pswd, state)"
                                   "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7','0')")
                        .arg(dataObject["userName"].toString())
                        .arg(dataObject["userNumber"].toString())
                        .arg(dataObject["userPassword"].toString())
                        .arg(dataObject["userSex"].toString())
                        .arg(dataObject["userSign"].toString())
                        .arg(dataObject["userHeadimg"].toString())
                        .arg(" ");
    emit request_SqlAddUserInfo(tcpThread_UserID,query);    //请求数据库添加用户信息
    return 1;
}

////---------------------------------------登录模块函数----------------------------------------------------------
/*  处理客户端用户登录请求
 *  dataObject：接收到的数据
*/
int TcpThread::handle_UserLoginRequest(QJsonObject dataObject)
{
    QString query = QStringLiteral("SELECT * FROM user "
                               "WHERE number = '%1' AND password = '%2';")
                            .arg(dataObject["userNumber"].toString())
                            .arg(dataObject["userPassword"].toString());
    emit request_VerifyUserInfo(tcpThread_UserID,query);      //发送信号验证登录信息
    return 1;
}
