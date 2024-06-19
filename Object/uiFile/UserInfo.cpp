#include "UserInfo.h"
#include "ui_UserInfo.h"

UserInfo::UserInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfo)
{
    ui->setupUi(this);
}

UserInfo::UserInfo(TcpThread *thread, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfo),
    tcpThread_Obj(thread)
{
    ui->setupUi(this);

    //初始化参数
    move_Ok = false;
    FriendList =  QSharedPointer<FriendList_Model>(new FriendList_Model(this));
    GroupList =  QSharedPointer<GroupList_Model>(new GroupList_Model(this));
    AiList =  QSharedPointer<AiList_Model>(new AiList_Model(this));
    Stacked_Layout = QSharedPointer<QStackedLayout>(new QStackedLayout());

    //请求Tcp线程发送文件至服务端
    connect(FriendList.data(),&FriendList_Model::relay_FilePathinUserInfo,this,&UserInfo::request_SendingFiletoServer);
    //请求Tcp线程发送图片信息至服务端
    connect(FriendList.data(),&FriendList_Model::relay_SendingImgJsoninUserInfo,this,&UserInfo::request_SendingFileJson);
    //请求Tcp线程发送接收文件请求至服务端
    connect(FriendList.data(),&FriendList_Model::relay_FileRequestinUserInfo,this,&UserInfo::request_FileRequesttoServer);
    //请求Tcp线程发送文件信息至服务端
    connect(FriendList.data(),&FriendList_Model::relay_SendingFileJsoninUserInfo,this,&UserInfo::request_SendingFileJson);
    //请求Tcp线程发送群聊信息至服务端
    connect(GroupList.data(),&GroupList_Model::relay_GroupMessageinUserInfo,this,&UserInfo::request_GroupMessagetoServer);
    //请求Tcp线程发送消息至服务端
    connect(FriendList.data(),&FriendList_Model::relay_SendingMessageinUserInfo,this,&UserInfo::request_SendingMessingtoServer);
    //请求Tcp线程发送表情至服务端
    connect(FriendList.data(),&FriendList_Model::relay_SendingEmotioninUserInfo,this,&UserInfo::request_SendingEmotiontoServer);
    //处理Tcp线程发送文件传输进度
    connect(tcpThread_Obj,&TcpThread::handle_ShowFileTransferSchedule,FriendList.data(),&FriendList_Model::handle_FileSchedule);
    //处理接收文件的信息至聊天界面显示
    connect(tcpThread_Obj,&TcpThread::handle_ShowFileInfoinChat,FriendList.data(),&FriendList_Model::handle_RelayFileInfoinChat);
    //处理Tcp线程接收文件传输进度
    connect(tcpThread_Obj,&TcpThread::handle_ShowReceiveFileSchedule,FriendList.data(),&FriendList_Model::handle_ReceiveFileSchedule);


    init_UserInfoWidget();  //初始化界面
    init_userInfoTcpConnect();  //初始化Tcp链接
    connect(&my_USER,&USER::new_USER,this,&UserInfo::new_UserInfoWidgetInfo);
}

UserInfo::~UserInfo()
{
    delete Setup_GUI;
    delete ui;
}

////------------------------------------表情发送模块函数-------------------------------------------------------------
/*  请求FriendList_Model处理好友发送的表情
 *  sendind：发送账号    emotion：表情
*/
int UserInfo::request_FriendEmotionToModel(const QString& sendind,const QString& emotion)
{
    FriendList->request_EmotionToFriendInfo(sendind,emotion);
}

/*  请求Tcp向服务器发送表情
 *  friendnumber：好友账号    emotion：表情
*/
int UserInfo::request_SendingEmotiontoServer(const QString& friendnumber, const QString& emotion)
{
    QJsonObject Json;
    Json.insert("type","friend_SendingEmotion");
    QJsonObject dataObj;
    dataObj.insert("sendingObj",my_USER.get_UserInfo(USER::Number));
    dataObj.insert("receiveObj",friendnumber);
    dataObj.insert("emotion",emotion);
    Json.insert("data",dataObj);
    QJsonDocument jsonDoc(Json);    //将Json格式转换为Byte格式
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
    tcpThread_Obj->sending_ToServer(byteArray);     //设置发送的数据
}

////------------------------------------文件发送模块函数-------------------------------------------------------------
/*  请求Tcp向服务器发送文件
 *  filePath：文件路径
*/
int UserInfo::request_SendingFiletoServer(const QString& filePath)
{
    tcpThread_Obj->sending_FileToServer(filePath);     //设置发送的数据
}

/*  请求Tcp向服务器发送文件Json信息
 *  sendingObj：文件Json信息
*/
int UserInfo::request_SendingFileJson(const QString& receiveFileObj, const QJsonObject& sendingObj)
{
    //设置发送的文件大小
    tcpThread_Obj->handle_SetReceiveFileObj(receiveFileObj);
    QJsonObject Object = sendingObj["fileInfo"].toObject();
    tcpThread_Obj->handle_SetSendingFileSize(Object["fileSize"].toInt());
    tcpThread_Obj->handle_SetSendingFileType(Object["fileName"].toString().section('.', -1));

    //将Json格式转换为Byte格式
    QJsonDocument jsonDoc(sendingObj);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
    tcpThread_Obj->sending_ToServer(byteArray);     //设置发送的数据
    return 1;
}

/*  请求Tcp向服务器发送接收文件请求
*/
int UserInfo::request_FileRequesttoServer()
{
    tcpThread_Obj->handle_FileStateAsJson();
}
////------------------------------------图片发送模块函数-------------------------------------------------------------
/*  请求FriendList_Model处理好友发送的图片
 *  sendind：发送账号    message：图片路径
*/
int UserInfo::handle_ShowFriendImgToModel(const QString &sendind, const QString &imgpath)
{
    FriendList->request_ImgToFriendInfo(sendind,imgpath);
    return 1;
}

////------------------------------------消息发送模块函数-------------------------------------------------------------
/*  请求TCP处理发送的群聊信息
 *  jsonObject：群聊信息
*/
int UserInfo::request_GroupMessagetoServer(const QJsonObject &jsonObject)
{
    //将Json格式转换为Byte格式
    QJsonDocument jsonDoc(jsonObject);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
    tcpThread_Obj->sending_ToServer(byteArray);     //设置发送的数据
    return 1;
}

/*  请求FriendList_Model处理好友发送的信息
 *  sendind：发送账号    message：消息
*/
int UserInfo::request_FriendMessageToModel(const QString& sendind,const QString& message)
{
    FriendList->request_MessageToFriendInfo(sendind,message);
    return 1;
}

/*  请求GroupList_Model处理发送的信息
 *  jsonObject：消息
*/
int UserInfo::request_GroupMessageToModel(const QJsonObject& jsonObject)
{
    if(jsonObject["sendingNumer"].toString() != my_USER.get_UserInfo(USER::Number)){
       GroupList->request_MessageToGroupInfo(jsonObject);
        return 1;
    }else{
        return 0;
    }
}

/*  请求Tcp向服务器发送私聊消息
 *  friendnumber：好友账号    message：消息
*/
int UserInfo::request_SendingMessingtoServer(const QString &friendnumber, const QString &message)
{
    QJsonObject Json;
    Json.insert("type","friend_SendingMessing");
    QJsonObject dataObj;
    dataObj.insert("sendingObj",my_USER.get_UserInfo(USER::Number));
    dataObj.insert("receiveObj",friendnumber);
    dataObj.insert("message",message);
    Json.insert("data",dataObj);
    QJsonDocument jsonDoc(Json);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);  //将Json格式转换为Byte格式
    tcpThread_Obj->sending_ToServer(byteArray);     //设置发送的数据
    return 1;
}

////------------------------------------Tcp模块函数-------------------------------------------------------------
/*  初始化Tcp链接
*/
int UserInfo::init_userInfoTcpConnect(){
    //处理设置Ai结果
    connect(tcpThread_Obj,&TcpThread::return_SetAiResult,this,&UserInfo::handle_SetAiResult);
    //处理获取Ai信息结果
    connect(tcpThread_Obj,&TcpThread::return_GetAiResult,this,&UserInfo::handle_GetAiResult);
    //请求关闭Tcp线程
    connect(this,&UserInfo::handle_TcpThreadClose,tcpThread_Obj,&TcpThread::handle_CloseThread);
    //处理返回群聊信息结果
    connect(tcpThread_Obj,&TcpThread::return_AddGroupInfo,this,&UserInfo::handle_ReturnGroupInfo);
    //处理返回好友信息结果
    connect(tcpThread_Obj,&TcpThread::return_AddFriendInfo,this,&UserInfo::handle_ReturnFriendInfo);
    //处理好友验证信息
    connect(tcpThread_Obj,&TcpThread::return_FriendVerify,this,&UserInfo::handle_FriendApplyFor);
    //处理新增群聊链接结果
    connect(tcpThread_Obj,&TcpThread::relay_AddGroupLinkResult,this,&UserInfo::handle_AddGroupLinkResult);
    //处理新增好友链接结果
    connect(tcpThread_Obj,&TcpThread::relay_AddFriendLinkResult,this,&UserInfo::handle_AddFriendLinkResult);
    //处理好友发送的图片
    connect(tcpThread_Obj,&TcpThread::relay_FriendImgToUserInfo,this,&UserInfo::handle_ShowFriendImgToModel);
    //处理群聊发送的信息
    connect(tcpThread_Obj,&TcpThread::relay_GroupMessingToUserInfo,this,&UserInfo::request_GroupMessageToModel);
    //处理好友发送的信息
    connect(tcpThread_Obj,&TcpThread::relay_FriendMessingToUserInfo,this,&UserInfo::request_FriendMessageToModel);
    //处理好友发送的表情
    connect(tcpThread_Obj,&TcpThread::relay_FriendEmotionToUserInfo,this,&UserInfo::request_FriendEmotionToModel);
    return 1;
}

////------------------------------------AI模块函数-------------------------------------------------------------
/*  请求服务器设置Ai信息
 *  type：操作类型
*/
int UserInfo::request_SetAiPackageAsJSON(const QString &type)
{
    QJsonObject Json;
    Json.insert("type",type);
    QJsonObject dataObj;
    dataObj.insert("Aisign",my_AI.handle_GetAiInfo(AI::aiSign));
    dataObj.insert("Ainame",my_AI.handle_GetAiInfo(AI::aiName));
    dataObj.insert("APIkey",my_AI.handle_GetAiInfo(AI::aiAPIKey));
    dataObj.insert("userNumber",my_USER.get_UserInfo(USER::Number));
    dataObj.insert("APIsecret",my_AI.handle_GetAiInfo(AI::aiAPISecret));
    Json.insert("data",dataObj);
    relay_VerifyResultPackageAsJSON(Json);
    return 1;
}

/*  请求服务器获取Ai信息
 *  type：操作类型
*/
int UserInfo::request_GetAiPackageAsJSON(const QString &type)
{
    QJsonObject Json;
    Json.insert("type",type);
    QJsonObject dataObj;
    dataObj.insert("userNumber",my_USER.get_UserInfo(USER::Number));
    Json.insert("data",dataObj);
    relay_VerifyResultPackageAsJSON(Json);
    return 1;
}

/*  处理设置Ai结果
 *  ok：设置结果   ai_Name：Ai昵称   ai_Sign：Ai介绍   ai_ApiKey：AiKey   ai_ApiSecret：AiSecret
*/
int UserInfo::handle_SetAiResult(bool ok,const QString &ai_Name,const QString &ai_Sign,
                               const QString &ai_ApiKey,const QString &ai_ApiSecret)
{
    if(ok){
        my_AI.handle_SetAllObject(ai_Name,ai_Sign,ai_ApiKey,ai_ApiSecret);
        return 1;
    }else{
        QMessageBox::information(nullptr,"提示","设置AI信息失败",QMessageBox::Ok);
        return 0;
    }
}

/*  处理获取Ai结果
 *  ok：设置结果   ai_Name：Ai昵称   ai_Sign：Ai介绍   ai_ApiKey：AiKey   ai_ApiSecret：AiSecret
*/
int UserInfo::handle_GetAiResult(bool ok,const QString &ai_Name,const QString &ai_Sign,
                                  const QString &ai_ApiKey,const QString &ai_ApiSecret)
{
    if(ok){
        my_AI.handle_SetAllObject(ai_Name,ai_Sign,ai_ApiKey,ai_ApiSecret);
        return 1;
    }else{
        QMessageBox::information(nullptr,"提示","当前用户未有智能管家",QMessageBox::Ok);
        return 0;
    }
}

////------------------------------------界面模块函数-------------------------------------------------------------
/*  初始化好友界面
 *  name：好友昵称    sign：好友个签    number：好友账号    headimg：好友头像    state：好友状态
*/
int UserInfo::add_InitFriendInfoWidget(const QString &name, const QString &sign, const QString &number,
                                       const QString headimg, const QString &state)
{
    FriendList->handle_AddFriend(name,sign,number,headimg,state);   //添加好友
    return 1;
}

/*  初始化群聊界面
 *  name：群聊昵称    id：群聊ID    headimg：群聊头像
*/
int UserInfo::add_InitGroupInfoWidget(const QString &name, const QString &id,
                                                const QString headimg)
{
    GroupList->handle_AddGroup(name,id,headimg);    //添加群聊
    return 1;
}

////------------------------------------添加好友(群组)模块函数-------------------------------------------------------------
/*  点击添加后关闭添加界面
*/
int UserInfo::handle_WindowClose()
{
    if(Addfriend_GUI != nullptr){
        delete Addfriend_GUI;
        Addfriend_GUI = nullptr;
    }
}
/*  处理好友是申请
 *  name：好友昵称    sex：好友性别    sing：好友个签    number：好友账号    headimg_Path：好友头像
*/
int UserInfo::handle_FriendApplyFor(const QString &name, const QString &sex, const QString &sign,
                                     const QString &number, const QString &headimg_Path)
{
    if(AddVerify_GUI != nullptr){
         delete AddVerify_GUI;
    }
    AddVerify_GUI = new AddVerify();
    //请求Tcp线程发送验证结果
    connect(AddVerify_GUI,&AddVerify::return_VerifyResult,this,&UserInfo::relay_VerifyResultPackageAsJSON);
    AddVerify_GUI->set_AddVerifyWindow("friend",name,sex,sign,number,headimg_Path);

    //获取主屏幕的几何信息
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect geometry = screen->geometry();

    //计算窗口的新位置，使其位于屏幕的右下角
    QPoint pos(geometry.width() - AddVerify_GUI->width(), geometry.height() - AddVerify_GUI->height() - 50);
    AddVerify_GUI->move(pos);
    AddVerify_GUI->show();
    return 1;
}

/*  处理新增好友链接结果操作
 *  jsondata：链接结果
*/
int UserInfo::handle_AddFriendLinkResult(const QJsonObject &jsonObject)
{
    QJsonObject data = jsonObject["data1"].toObject();
    if(jsonObject["code"].toString() == "65"){
        if(data["friendnumber"].toString() != my_USER.get_UserInfo(USER::Number)){
            add_InitFriendInfoWidget(data["friendname"].toString(),data["friendsign"].toString(),
                                    data["friendnumber"].toString(),data["friendheadimg"].toString(),
                                    data["friendstate"].toString());
        }else{
            data = jsonObject["data2"].toObject();
            add_InitFriendInfoWidget(data["friendname"].toString(),data["friendsign"].toString(),
                                    data["friendnumber"].toString(),data["friendheadimg"].toString(),
                                    data["friendstate"].toString());
        }
        QMessageBox::information(nullptr,"提示","添加好友成功！",QMessageBox::Ok);
        return 1;
    }else{
        QMessageBox::information(nullptr,"提示","重复添加好友或数据异常！",QMessageBox::Ok);
        return 0;
    }
}

/*  处理新增群聊链接结果操作
 *  jsondata：链接结果
*/
int UserInfo::handle_AddGroupLinkResult(const QJsonObject &jsonObject)
{
    QJsonObject data = jsonObject["data"].toObject();
    if(jsonObject["code"].toString() == "93"){
        add_InitGroupInfoWidget(data["groupname"].toString(),data["groupnumber"].toString(),data["groupheadimg"].toString());
        QMessageBox::information(nullptr,"提示","添加群聊成功！",QMessageBox::Ok);
        return 1;
    }else{
        QMessageBox::information(nullptr,"提示","重复添加群聊或数据异常！",QMessageBox::Ok);
        return 0;
    }
}

/*  将验证结果转发至TcpThread发送
 *  jsondata：验证结果
*/
int UserInfo::relay_VerifyResultPackageAsJSON(const QJsonObject &jsondata)
{
    //将Json格式转换为Byte格式
    QJsonDocument jsonDoc(jsondata);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
    tcpThread_Obj->sending_ToServer(byteArray);     //设置发送的数据
    return 1;
}

/*  处理请求好友验证操作
*/
int UserInfo::handle_ApplyForFriendVerify(const QString &type, const QString &number)
{
    QJsonObject Json;
    Json.insert("type",type);
    QJsonObject dataObj;
    dataObj.insert("friendNumber",number);  //要添加好友的账号
    dataObj.insert("userNumber",my_USER.get_UserInfo(USER::Number));
    Json.insert("data",dataObj);
    handle_WindowClose();
    relay_VerifyResultPackageAsJSON(Json);
    return 1;
}

/*  处理请求群聊验证操作
*/
int UserInfo::handle_ApplyForGroupVerify(const QString &type, const QString &number)
{
    QJsonObject Json;
    Json.insert("type",type);
    QJsonObject dataObj;
    dataObj.insert("groupNumber",number);  //要添加群聊的账号
    Json.insert("data",dataObj);
    handle_WindowClose();
    relay_VerifyResultPackageAsJSON(Json);
    return 1;
}

/*  处理返回的好友信息结果
 *  code：错误码    name：查询的好友昵称    state：查询的好友状态    sex：查询的好友性别    sign：查询的好友个签
 *  number：查询的好友账号    headimg_Path：查询的好友头像
*/
int UserInfo::handle_ReturnFriendInfo(const QString& code, const QString& state, const QString &name,
                                       const QString &sex, const QString &sign, const QString &number,
                                       const QString &headimg_Path)
{
    emit relay_FriendInfoHandle(code,state,name,sex,sign,number,headimg_Path); //转发至AddInfo界面处理
    return 1;
}

/*  处理返回的群聊信息结果
 *  code：错误码    number：查询的群号码    name：查询的群聊昵称    headimg_Path：查询的群聊头像
*/
int UserInfo::handle_ReturnGroupInfo(const QString& code, const QString &number, const QString &name,
                                     const QString &headimg_Path)
{
    emit relay_GroupInfoHandle(code,number,name,headimg_Path); //转发至AddInfo界面处理
    return 1;
}

/*  获取添加的好友信息
 *  type：操作类型    number：好友账号
*/
int UserInfo::request_AddFriendInfo(const QString &type, const QString &number)
{
    //设置Json数据，处理申请好友验证操作
    QJsonObject Json;
    Json.insert("type",type);
    QJsonObject dataObj;
    dataObj.insert("friendNumber",number);
    Json.insert("data",dataObj);
    relay_VerifyResultPackageAsJSON(Json);
    return 1;
}

/*  获取添加的群聊信息
 *  type：操作类型    number：群聊账号
*/
int UserInfo::request_AddGroupInfo(const QString &type, const QString &number)
{
    //设置Json数据，处理申请好友验证操作
    QJsonObject Json;
    Json.insert("type",type);
    QJsonObject dataObj;
    dataObj.insert("groupNumber",number);
    Json.insert("data",dataObj);
    relay_VerifyResultPackageAsJSON(Json);
    return 1;
}

/*  添加好友或群组
*/
void UserInfo::on_addfriend_Btn_clicked()
{
    if(Addfriend_GUI == nullptr){
        Addfriend_GUI = new AddInfo();
    }
    //请求好友信息界面查询添加群聊的信息
    connect(Addfriend_GUI,&AddInfo::get_AddGroupInfo,this,&UserInfo::request_AddGroupInfo);
    //请求好友信息界面查询添加好友的信息
    connect(Addfriend_GUI,&AddInfo::get_AddFriendInfo,this,&UserInfo::request_AddFriendInfo);
    //转发至AddInfo界面处理查询到的群聊信息
    connect(this,&UserInfo::relay_GroupInfoHandle,Addfriend_GUI,&AddInfo::handle_GroupInfoinWidget);
    //转发至AddInfo界面处理查询到的好友信息
    connect(this,&UserInfo::relay_FriendInfoHandle,Addfriend_GUI,&AddInfo::handle_FriendInfoinWidget);
    //转发至Tcp线程处理请求群聊验证
    connect(Addfriend_GUI,&AddInfo::request_ApplyForGroupVerify,this,&UserInfo::handle_ApplyForGroupVerify);
    //转发至Tcp线程处理请求好友验证
    connect(Addfriend_GUI,&AddInfo::request_ApplyForFriendVerify,this,&UserInfo::handle_ApplyForFriendVerify);
    Addfriend_GUI->show();  //显示添加好友界面
}

////------------------------------------界面控件函数-------------------------------------------------------------
/*  初始化界面
*/
int UserInfo::init_UserInfoWidget()
{
    //初始化对象
    ai_Ok = false;
    Setup_GUI = nullptr;
    Addfriend_GUI = nullptr;
    AddVerify_GUI = nullptr;

    //初始化控件
    QPixmap headimg(my_USER.get_UserInfo(USER::Headimg));
    ui->userHead_Lab->setPixmap(headimg);
    ui->userName_Lab->setText(my_USER.get_UserInfo(USER::Name));
    ui->userSign_Lab->setText(my_USER.get_UserInfo(USER::Sign));
    ui->userNumber_Lab->setText(my_USER.get_UserInfo(USER::Number));

    //注册事件过滤器
    ui->friend_Lab->installEventFilter(this);
    ui->group_Lab->installEventFilter(this);
    ui->Ai_Lab->installEventFilter(this);

    //设置界面透明与去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    //设置组件与布局
    Stacked_Layout.data()->addWidget(FriendList.data());
    Stacked_Layout.data()->addWidget(GroupList.data());
    Stacked_Layout.data()->addWidget(AiList.data());
    ui->Middle->setLayout(Stacked_Layout.data());
    return 1;
}

/*  关闭界面函数
*/
void UserInfo::on_clos_Btn_clicked()
{
    emit handle_TcpThreadClose(my_USER.get_UserInfo(USER::Number)); //请求关闭线程
    this->close();
}

/*  最小化界面函数
*/
void UserInfo::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  设置界面函数
*/
void UserInfo::on_setup_Btn_clicked()
{
    if(Setup_GUI == nullptr){
        Setup_GUI = new SetUp();
        //申请服务端设置Ai信息
        connect(Setup_GUI,&SetUp::relay_UserWidgetSetAiInfo,this,&UserInfo::request_SetAiPackageAsJSON);
        //申请服务端获取Ai信息
        connect(Setup_GUI,&SetUp::relay_UserWidgetGetAiInfo,this,&UserInfo::request_GetAiPackageAsJSON);
    }

    Setup_GUI->show();
}

/*  更新控件消息
*/
int UserInfo::new_UserInfoWidgetInfo()
{
    //设置控件信息
    QPixmap headimg(my_USER.get_UserInfo(USER::Headimg));
    ui->userHead_Lab->setPixmap(headimg);
    ui->userName_Lab->setText(my_USER.get_UserInfo(USER::Name));
    ui->userSign_Lab->setText(my_USER.get_UserInfo(USER::Sign));
    ui->userNumber_Lab->setText(my_USER.get_UserInfo(USER::Number));
    return 1;
}

////------------------------------------事件模块函数-------------------------------------------------------------
/*  鼠标点击事件
 *  event：事件
*/
void UserInfo::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

/*  鼠标释放事件
 *  event：事件
*/
void UserInfo::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  鼠标移动事件
 *  event：事件
*/
void UserInfo::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

/*  事件过滤器
 *  watched：对象    event：事件
 *  返回值：bool(操作成功为真，操作失败为假)
*/
bool UserInfo::eventFilter(QObject *watched, QEvent *event)
{
    //底部换页函数
    if((event->type()==QEvent::MouseButtonPress) && (watched==ui->friend_Lab)){
        Stacked_Layout->setCurrentIndex(0);     //显示好友信息界面
    }
    else if((event->type()==QEvent::MouseButtonPress) && (watched==ui->group_Lab)){
        Stacked_Layout->setCurrentIndex(1);     //显示群聊信息界面
    }
    else if((event->type()==QEvent::MouseButtonPress) && (watched==ui->Ai_Lab)){
        Stacked_Layout->setCurrentIndex(2);     //显示AI信息界面
        if(!ai_Ok){     //判断是否获取过Ai信息，防止重复获取
            request_GetAiPackageAsJSON("getAI");
            ai_Ok = true;
        }
    }
    return true;
}
