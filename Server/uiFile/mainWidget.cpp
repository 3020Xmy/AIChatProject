#include "mainWidget.h"
#include "ui_mainWidget.h"

mainWidget::mainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainWidget)
{
    ui->setupUi(this);

    init_MainWidget();  //初始化界面
    init_SqlModule();   //初始化数据库模块
    init_TcpModule();   //初始化Tcp模块
}

mainWidget::~mainWidget()
{
    delete ui;
}

////--------------------------------------图片发送模块函数--------------------------------------------------
/*  处理转发的文件Json数据
 *  number：接收的用户   path：图片路径    imgJson：Json数据
*/
void mainWidget::handle_FriendSendingFileJson(const QString& number, const QString& path, const QJsonObject &imgJson)
{
    emit reques_FriendFileJsonToClient(number,path,imgJson);
}

////--------------------------------------表情发送模块函数--------------------------------------------------
/*  处理转发的好友表情
 *  sending：发送者    receive：接收者    emotion：消息
*/
int mainWidget::handle_FriendSendingEmotion(const QString &sending, const QString &receive,
                                            const QString &emotion)
{
    QJsonObject rootObj;
    rootObj.insert("code",71);
    rootObj.insert("type","receive_FriendEmotion");
    QJsonObject dataObj;
    dataObj.insert("sendingObj",sending);
    dataObj.insert("receiveObj",receive);
    dataObj.insert("emotion",emotion);
    rootObj.insert("data",dataObj);
    emit reques_FriendEmotionToClient(receive,rootObj);
}

////--------------------------------------消息发送模块函数--------------------------------------------------
/*  处理转发的好友消息
 *  sending：发送者    receive：接收者    message：消息
*/
int mainWidget::handle_FriendSendingMessage(const QString &sending, const QString &receive,
                                            const QString &message)
{
    QJsonObject rootObj;
    rootObj.insert("code",68);
    rootObj.insert("type","receive_FriendMessage");
    QJsonObject dataObj;
    dataObj.insert("sendingObj",sending);
    dataObj.insert("receiveObj",receive);
    dataObj.insert("message",message);
    rootObj.insert("data",dataObj);
    emit reques_FriendMessageToClient(receive,rootObj);
}

/*  处理转发的群聊消息
 *  dataObjecte：消息
*/
void mainWidget::handle_GroupSendingMessage(QJsonObject dataObject)
{
    emit reques_GroupMessageToClient(dataObject);
}

////--------------------------------------Tcp模块函数--------------------------------------------------
/*  初始化Tcp模块
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int mainWidget::init_TcpModule()
{
    //初始化对象
    tcpSocket = new QTcpSocket;
    tcpServer = new QTcpServer(this);
    connect(tcpServer,&QTcpServer::newConnection,this,&mainWidget::init_TcpConnection);

    get_LocalIPv4();    //获取IPv4地址
    quint16 prot= 13020;//监听端口
    tcpServer->listen(QHostAddress::Any,prot);  //开始监听
    return 1;
}

/*  获取本机IPV4地址
 *  返回值：int(错误码，-1为异常，0为错误，1为无误)
*/
int mainWidget::get_LocalIPv4()
{
    QString hostName = QHostInfo::localHostName();     //获取主机设备名
    QHostInfo hostInfo = QHostInfo::fromName(hostName);//获取主机信息
    QString localIP = " ";
    QList<QHostAddress> addList = hostInfo.addresses();//获取主机地址列表
    if(addList.isEmpty()){  //未获取到地址
        return 0;
    }
    else{
        foreach(const QHostAddress& item,addList){
            if(item.protocol() == QAbstractSocket::IPv4Protocol){
                localIP = item.toString();
                ui->TcpIpv4_Box->addItem(QIcon(":/becurrent/becurrent/IPdizhi_1.png"),localIP);
            }
        }
        return 1;
    }
    return -1;
}

/*  初始化连接
*/
int mainWidget::init_TcpConnection()
{
    //获取第一个链接的客户端
    tcpSocket = tcpServer->nextPendingConnection();
    TcpConnect_Number +=1;
    tcp_Thread = new TcpThread(tcpSocket,TcpConnect_Number,this);

    //请求关闭线程
    connect(this,&mainWidget::request_Disconnect,tcp_Thread,&TcpThread::handle_TCPDisconnect);
    //请求UserInfo界面更新用户账号信息
    connect(tcp_Thread,&TcpThread::request_NewUserNumber,UserInfo_GUI,&UserInfo::set_NumberItem);
    //请求UserInfo界面更新用户操作信息
    connect(tcp_Thread,&TcpThread::request_NewUserOperator,UserInfo_GUI,&UserInfo::set_TypeItem);
    //返回用户项Id至线程
    connect(UserInfo_GUI,&UserInfo::return_UserItemId,tcp_Thread,&TcpThread::handle_SetUserItemId);
    //请求UserInfo界面更新用户连接信息
    connect(tcp_Thread,&TcpThread::request_NewUserConnect,UserInfo_GUI,&UserInfo::add_NewUserInfoItem);
    //请求数据库更新用户状态为离线
    connect(tcp_Thread,&TcpThread::request_SqlNewUserStateinExit,sql_Thread,&SqlThread::handle_NewUserStateinExit);

    //请求数据库添加注册用户信息操作
    connect(tcp_Thread,&TcpThread::request_SqlAddUserInfo,sql_Thread,&SqlThread::handle_RegisterUserResult);
    connect(sql_Thread,&SqlThread::return_UserRegisterResult,tcp_Thread,&TcpThread::return_ClientData);

    //请求数据库验证用户登录信息
    connect(tcp_Thread,&TcpThread::request_VerifyUserInfo,sql_Thread,&SqlThread::handle_LoginVerifyUserData);
    connect(sql_Thread,&SqlThread::return_LoginVerifyUserResult,tcp_Thread,&TcpThread::return_ClientData);

    //请求数据库添加加密数据
    connect(tcp_Thread,&TcpThread::request_SaveEncryptData,sql_Thread,&SqlThread::handle_AddEncryptData);
    connect(sql_Thread,&SqlThread::return_AddEncryptResult,tcp_Thread,&TcpThread::return_ClientData);

    //请求数据库查询Ai信息
    connect(tcp_Thread,&TcpThread::request_SqlSeleteAiInfo,sql_Thread,&SqlThread::handle_GetAiInfo);
    connect(sql_Thread,&SqlThread::return_GetAiOperateResult,tcp_Thread,&TcpThread::return_ClientData);

    //请求数据库设置Ai数据
    connect(tcp_Thread,&TcpThread::request_SqlSetAiInfo,sql_Thread,&SqlThread::handle_SetAiInfo);
    connect(sql_Thread,&SqlThread::return_SetAiResult,tcp_Thread,&TcpThread::return_ClientData);

    //请求数据库查询好友信息
    connect(tcp_Thread,&TcpThread::request_SqlSeleteFriendInfo,sql_Thread,&SqlThread::handle_SeleteFriendInfo);
    connect(sql_Thread,&SqlThread::return_SeleteinFriendResult,tcp_Thread,&TcpThread::return_ClientData);

    //请求数据库查询群聊信息
    connect(tcp_Thread,&TcpThread::request_SqlSeleteGroupInfo,sql_Thread,&SqlThread::handle_SeleteGroupInfo);
    connect(sql_Thread,&SqlThread::return_SeleteinGroupResult,tcp_Thread,&TcpThread::return_ClientData);

    //申请好友验证操作
    connect(tcp_Thread,&TcpThread::relay_AddFriendVerify,sql_Thread,&SqlThread::handle_AddFriendOperator);
    connect(sql_Thread,&SqlThread::return_ApplyForFriendVerifyResult,tcp_Thread,&TcpThread::return_ClientData);

    //请求数据库添加好友链接数据
    connect(tcp_Thread,&TcpThread::request_AddFriendLinkData,sql_Thread,&SqlThread::handle_AddFriendLinkData);
    connect(sql_Thread,&SqlThread::return_AddFriendLinkDataResult,tcp_Thread,&TcpThread::return_ClientData);

    //请求数据库添加群聊链接数据
    connect(tcp_Thread,&TcpThread::request_AddGroupLinkData,sql_Thread,&SqlThread::handle_AddGroupLinkData);
    connect(sql_Thread,&SqlThread::return_GroupLinkResult,tcp_Thread,&TcpThread::return_ClientData);

    //请求mainWidget转发好友消息
    connect(tcp_Thread,&TcpThread::relay_MessageToMainWidget,this,&mainWidget::handle_FriendSendingMessage);
    connect(this,&mainWidget::reques_FriendMessageToClient,tcp_Thread,&TcpThread::return_ClientData);

    //请求mainWidget转发群聊消息
    connect(tcp_Thread,&TcpThread::relay_GroupMessageToMainWidget,this,&mainWidget::handle_GroupSendingMessage);
    connect(this,&mainWidget::reques_GroupMessageToClient,tcp_Thread,&TcpThread::return_GroupinClien);

    //请求mainWidget转发好友表情
    connect(tcp_Thread,&TcpThread::relay_EmotionToMainWidget,this,&mainWidget::handle_FriendSendingEmotion);
    connect(this,&mainWidget::reques_FriendEmotionToClient,tcp_Thread,&TcpThread::return_ClientData);

    //请求mainWidget转发好友文件信息
    connect(tcp_Thread,&TcpThread::relay_FileJsonToMainWidget,this,&mainWidget::handle_FriendSendingFileJson);
    connect(this,&mainWidget::reques_FriendFileJsonToClient,tcp_Thread,&TcpThread::handle_RequestFileInfo);


    QThreadPool::globalInstance()->start(tcp_Thread);//启动线程
    return 1;
}

////--------------------------------------Sql模块函数--------------------------------------------------
/*  初始化数据库
*/
int mainWidget::init_SqlModule()
{
    sql_Thread = new SqlThread(this);

    //处理关闭数据库线程
    connect(this,&mainWidget::request_Disconnect,sql_Thread,&SqlThread::handle_SQLDisconnect);
    QThreadPool::globalInstance()->start(sql_Thread);//启动线程
    return 1;
}

////--------------------------------------事件模块函数--------------------------------------------------
/*  鼠标点击事件
*/
void mainWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

/*  鼠标释放事件
*/
void mainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  鼠标移动事件
*/
void mainWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

////--------------------------------------界面模块函数--------------------------------------------------
/*  初始化界面
*/
int mainWidget::init_MainWidget()
{
    //初始化对象
    UserInfo_GUI = new UserInfo(ui->bottom_Widget);
    SqlInfo_GUI = new SqlInfo(ui->bottom_Widget);
    FileInfo_GUI = new FileInfo(ui->bottom_Widget);
    GroupInfo_GUI = new GroupInfo(ui->bottom_Widget);

    //优先显示用户信息窗口
    UserInfo_GUI->show();
    SqlInfo_GUI->hide();
    FileInfo_GUI->hide();
    GroupInfo_GUI->hide();

    setWindowFlags(Qt::WindowType::FramelessWindowHint);    //设置界面去掉边框
    return 1;
}

/*  关闭窗口函数
*/
void mainWidget::on_clos_Btn_clicked()
{
    this->close();
    emit request_Disconnect();   //请求关闭所有线程
}

/*  缩小窗口函数
*/
void mainWidget::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  用户信息按钮
*/
void mainWidget::on_userinfo_But_clicked()
{
    //显示用户信息窗口
    UserInfo_GUI->show();

    //关闭其他窗口
    SqlInfo_GUI->hide();
    FileInfo_GUI->hide();
    GroupInfo_GUI->hide();
}

/*  群聊信息窗口
*/
void mainWidget::on_groupinfo_But_clicked()
{
    //显示群聊信息窗口
    GroupInfo_GUI->show();

    //关闭其他窗口
    SqlInfo_GUI->hide();
    FileInfo_GUI->hide();
    UserInfo_GUI->hide();
}

/*  文件转发信息窗口
*/
void mainWidget::on_fileinfo_But_clicked()
{
    //显示文件转发信息窗口
    FileInfo_GUI->show();

    //关闭其他窗口
    SqlInfo_GUI->hide();
    UserInfo_GUI->hide();
    GroupInfo_GUI->hide();
}

/*  数据库信息窗口
*/
void mainWidget::on_sqlinfo_But_clicked()
{
    //显示数据库信息窗口
    SqlInfo_GUI->show();

    //关闭其他窗口
    FileInfo_GUI->hide();
    UserInfo_GUI->hide();
    GroupInfo_GUI->hide();
}

