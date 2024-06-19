#include "FriendInfo.h"
#include "ui_FriendInfo.h"

FriendInfo::FriendInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendInfo)
{
    ui->setupUi(this);
}

FriendInfo::FriendInfo(const QString &name, const QString &sign,
                       const QString &number, const QString headimg,
                       const QString &state,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendInfo)
{
    ui->setupUi(this);

    //初始化界面
    handle_FriendInfoinitWidget(name,sign,number,headimg,state);
}

FriendInfo::~FriendInfo()
{
    delete ui;
}

////---------------------------------------信息发送模块函数-------------------------------------------------------
/*  处理转发的消息
 *  friendnumber：好友账号    message：消息
*/
int FriendInfo::handle_RelaySengingMessage(const QString& friendnumber, const QString& message)
{
    emit relay_SendingMessageinModel(friendnumber,message); //转发至FriendList_Model处理发送的消息
    return 1;
}

/*  处理好友信息
 *  sendind：好友账号   message：信息
*/
int FriendInfo::request_MessageToFriendChat(const QString &sendind, const QString &message)
{
    if(Chat.data()->get_FriendNumber() == sendind){
        Chat.data()->show();
        Chat.data()->handle_FriendMessage(message);
        return 1;
    }else{
        return 0;
    }
}

////---------------------------------------表情发送模块函数-------------------------------------------------------
/*  处理转发的消息
 *  friendnumber：好友账号    emotion：表情
*/
int FriendInfo::handle_RelaySengingEmotion(const QString& friendnumber, const QString& emotion)
{
    emit relay_SendingEmotioninModel(friendnumber,emotion); //转发至FriendList_Model处理发送的消息
    return 1;
}

/*  处理好友信息
 *  sendind：好友账号   message：信息
*/
int FriendInfo::request_EmotionToFriendChat(const QString &sendind, const QString &message)
{
    if(Chat.data()->get_FriendNumber() == sendind){
        Chat.data()->show();
        Chat.data()->handle_FriendEmotion(message);
        return 1;
    }else{
        return 0;
    }
}

////---------------------------------------文件发送模块函数-------------------------------------------------------
/*  转发发送的文件路径给FriendMode
 *  filepath：文件路径
*/
int FriendInfo::relay_SendingFile(const QString &filepath)
{
    emit relay_FilePathinFriendModel(filepath);
    return 1;
}

/*  处理转发的文件Json消息
 *  sendingObj：发送的文件Json信息
*/
int FriendInfo::handle_RelaySengingFileJson(const QString& receiveFileObj, const QJsonObject& sendingObj)
{
    emit relay_SendingFileJsoninModel(receiveFileObj,sendingObj); //转发至FriendList_Model处理发送的文件
    return 1;
}

/*  处理转发的文件Json消息
 *  sendingObj：发送的文件Json信息
*/
int FriendInfo::handle_RelayFileRequest()
{
    emit handle_RelayFileRequestinModel();
    return 1;
}

/*  处理转发发送的文件进度
 *  Obj：接收的对象    size：文件进度
*/
int FriendInfo::relay_FileSchedule(const QString& Obj,qint64 size)
{
    if(Chat.data()->get_FriendNumber() == Obj){
        Chat.data()->show();
        Chat.data()->handle_SendingFileSchedule(size);
        return 1;
    }else{
        return 1;
    }
}

/*  处理好友发送的的文件信息
 *  receiveFileObj：接收的信息    sendingObj：发送的对象
*/
int FriendInfo::handle_FileInfo(const QString &receiveFileObj, const QJsonObject &sendingObj)
{
    if(Chat.data()->get_FriendNumber() == receiveFileObj){
        Chat.data()->show();
        Chat.data()->handle_ShowFileBox(sendingObj);
        return 1;
    }else{
        return 0;
    }
}

/*  处理转发接收的文件进度
 *  Obj：接收的对象    size：接收的文件进度
*/
int FriendInfo::relay_ReceiveFileSchedule(const QString& Obj,qint64 size)
{
    if(Chat.data()->get_FriendNumber() == Obj){
        Chat.data()->show();
        Chat.data()->handle_ReceiveFileSchedule(size);
        return 1;
    }else{
        return 0;
    }
}

////---------------------------------------图片发送模块函数-------------------------------------------------------
/*  处理转发的图片Json消息
 *  sendingObj：发送的图片Json信息
*/
int FriendInfo::handle_RelaySengingImgJson(const QJsonObject& sendingObj)
{
    emit relay_SendingImgJsoninModel(sendingObj); //转发至FriendList_Model处理发送的图片
    return 1;
}

/*  处理好友图片
 *  sendind：好友账号   ImgPath：图片
*/
int FriendInfo::request_ImgToFriendChat(const QString& sendind,const QString& ImgPath)
{
    if(Chat.data()->get_FriendNumber() == sendind){
        Chat.data()->show();
        Chat.data()->handle_FriendImg(ImgPath);
        return 1;
    }else{
        return 0;
    }
}

////---------------------------------------事件操作函数-------------------------------------------------------
/*  双击好友显示对话框
 *  event：事件
*/
void FriendInfo::mouseDoubleClickEvent(QMouseEvent *event)
{
    Chat.data()->show();
    event->accept();
}

////---------------------------------------界面操作函数--------------------------------------------------------
/*  初始化界面
 *  name：优化昵称    sign：用户个签    number：用户账号    headimg：用户头像    state：用户状态
*/
int FriendInfo::handle_FriendInfoinitWidget(const QString &name, const QString &sign,
                                           const QString &number, const QString headimg,const QString &state)
{
    //初始化参数
    Chat = QSharedPointer<FriendChat>(new FriendChat(name,sign,number,headimg,state));
    //转发至FriendList_Model处理发送的文件
    connect(Chat.data(),&FriendChat::handle_SendingFilePath,this,&FriendInfo::relay_SendingFile);
    //转发至FriendList_Model处理发送的消息
    connect(Chat.data(),&FriendChat::handle_SendingMessage,this,&FriendInfo::handle_RelaySengingMessage);
    //转发至FriendList_Model处理发送的表情
    connect(Chat.data(),&FriendChat::handle_SendingEmotion,this,&FriendInfo::relay_SendingEmotioninModel);
    //转发至FriendList_Model处理文件接收请求
    connect(Chat.data(),&FriendChat::handle_ForwardFileRequest,this,&FriendInfo::handle_RelayFileRequest);
    //转发至FriendList_Model处理发送的图片Json信息
    connect(Chat.data(),&FriendChat::handle_SendingImgInfoJson,this,&FriendInfo::handle_RelaySengingImgJson);
    //转发至FriendList_Model处理发送的文件Json信息
    connect(Chat.data(),&FriendChat::handle_SendingFileInfoJson,this,&FriendInfo::handle_RelaySengingFileJson);

    //初始化姓名，个签，账号，头像
    ui->userName_Lab->setText(name);
    ui->userSign_Lab->setText(sign);
    ui->userNumber_Lab->setText(number);
    ui->userHead_Lab->setScaledContents(true);  //设置头像大小自适应
    QPixmap originalPixmap(headimg);
    originalPixmap = originalPixmap.scaled(ui->userHead_Lab->width(),
                                           ui->userHead_Lab->height(), Qt::KeepAspectRatio);
    ui->userHead_Lab->setPixmap(originalPixmap);

    if(state == "1"){   //设置头像状态样式
        ui->userHead_Lab->setStyleSheet("border: 2px solid green;");
    }else{
        ui->userHead_Lab->setStyleSheet("border: 2px solid black;");
    }
    return 1;
}
