#include "FriendList_Model.h"

FriendList_Model::FriendList_Model(QWidget *parent)
    :QToolBox(parent)
{
    //初始化对象
    len = 0;
    handle_AddFriendList("好友");
}

FriendList_Model::~FriendList_Model()
{

}

////---------------------------------------界面模块函数-------------------------------------------------------
/*  新增好友
 *  name：好友昵称    sign：好友个签   number：好友账号   headimg：好友头像
*/
int FriendList_Model::handle_AddFriend(const QString &name, const QString &sign,
                                 const QString &number, const QString headimg,const QString &state)
{
    FriendInfo* Demo = new FriendInfo(name,sign,number,headimg,state);
    QSharedPointer<FriendInfo> info_Demo(Demo); //使用智能指针托管
    FriendInfo_Vector.append(info_Demo);
    handle_FriendInsertlist(ListWidget_Vector[0],FriendInfo_Vector[len]);
    len += 1;
    //转发至FriendMode处理发送的文件路径
    connect(Demo,&FriendInfo::relay_FilePathinFriendModel,this,&FriendList_Model::handle_FilePathinUserInfo);
    //转发至UserInfo界面处理发送的信息为图片
    connect(Demo,&FriendInfo::relay_SendingImgJsoninModel,this,&FriendList_Model::handle_SendingImgJsoninUserInfo);
    //转发至UserInfo界面处理发送的信息
    connect(Demo,&FriendInfo::relay_SendingMessageinModel,this,&FriendList_Model::handle_SendingMessageinUserInfo);
    //转发至UserInfo界面处理发送的表情
    connect(Demo,&FriendInfo::relay_SendingEmotioninModel,this,&FriendList_Model::handle_SendingEmotioninUserInfo);
    //转发至UserInfo界面处理发送的信息为文件
    connect(Demo,&FriendInfo::relay_SendingFileJsoninModel,this,&FriendList_Model::handle_SendingFileJsoninUserInfo);
    //转发至UserInfo界面处理接收文件请求
    connect(Demo,&FriendInfo::handle_RelayFileRequestinModel,this,&FriendList_Model::handle_RelayFileRequestinUserInfo);
    return 1;
}

/*  新增分组
 *  groupname：分组名称
*/
int FriendList_Model::handle_AddFriendList(const QString &groupname)
{
    QSharedPointer<QListWidget> Demo(new QListWidget);   //使用智能指针托管
    ListWidget_Vector.append(Demo);
    this->addItem(Demo.data(),groupname);
    return 1;
}

/*  将好友插入分组
 *  fist：指定分组容器    friendinfo：好友信息
*/
int FriendList_Model::handle_FriendInsertlist(QSharedPointer<QListWidget> &list,
                                              QSharedPointer<FriendInfo> &friendinfo)
{
    QListWidgetItem *item = new QListWidgetItem();//新建替换的Item
    item->setSizeHint(QSize(270, 85));
    list->addItem(item);
    list->setItemWidget(item, friendinfo.data()); //修改Item为自定义样式(FriendInfo)
    this->update();
    return 1;
}

////---------------------------------------信息发送模块函数-------------------------------------------------------
/*  转发至UserInfo界面处理发送的信息
 *  friendnumber：好友账号    message：消息
*/
int FriendList_Model::handle_SendingMessageinUserInfo(const QString &friendnumber, const QString &message)
{
    emit relay_SendingMessageinUserInfo(friendnumber,message);
}

/*  处理好友发送的信息
 *  sendind：好友账号   message：信息
*/
int FriendList_Model::request_MessageToFriendInfo(const QString &sendind, const QString &message)
{
    for(int i = 0; i<len ;++i){
        FriendInfo_Vector[i].data()->request_MessageToFriendChat(sendind,message);
    }
}

/*  处理好友发送的图片
 *  sendind：好友账号   ImgPath：图片路径
*/
int FriendList_Model::request_ImgToFriendInfo(const QString &sendind, const QString &ImgPath)
{
    for(int i = 0; i<len ;++i){
        FriendInfo_Vector[i].data()->request_ImgToFriendChat(sendind,ImgPath);
    }
}

////---------------------------------------表情发送模块函数-------------------------------------------------------
/*  转发至UserInfo界面处理发送的表情
 *  friendnumber：好友账号    emotion：消息
*/
int FriendList_Model::handle_SendingEmotioninUserInfo(const QString &friendnumber, const QString &emotion)
{
    emit relay_SendingEmotioninUserInfo(friendnumber,emotion);
}

/*  处理好友发送的表情
 *  sendind：好友账号   emotion：表情
*/
int FriendList_Model::request_EmotionToFriendInfo(const QString &sendind, const QString &emotion)
{
    for(int i = 0; i<len ;++i){
        FriendInfo_Vector[i].data()->request_EmotionToFriendChat(sendind,emotion);
    }
}

////---------------------------------------图片发送模块函数-------------------------------------------------------
/*  转发至UserInfo界面处理发送的图片Json信息
 *  sendingObj：图片Json信息
*/
int FriendList_Model::handle_SendingImgJsoninUserInfo(const QJsonObject& sendingObj)
{
    emit relay_SendingImgJsoninUserInfo(" ",sendingObj);
}

////---------------------------------------文件模块函数-------------------------------------------------------
/*  处理发送的文件传输进度
 *  Obj：接收对象    size：传输进度
*/
void FriendList_Model::handle_FileSchedule(const QString& Obj,qint64 size)
{
    for(int i = 0; i<len ;++i){
        FriendInfo_Vector[i].data()->relay_FileSchedule(Obj,size);
    }
}

/*  处理接收的文件接收进度
 *  size：接收进度
*/
void FriendList_Model::handle_ReceiveFileSchedule(const QString& Obj,qint64 size)
{
    for(int i = 0; i<len ;++i){
        FriendInfo_Vector[i].data()->relay_ReceiveFileSchedule(Obj,size);
    }
}

//  将文件信息转发至聊天界面显示
void FriendList_Model::handle_RelayFileInfoinChat(const QString &sendingObj, const QJsonObject &jsonObject)
{
    for(int i = 0; i<len; ++i){
        FriendInfo_Vector[i].data()->handle_FileInfo(sendingObj,jsonObject);
    }
}

/*  处理发送的文件路径
 *  filePaht：文件路径
*/
int FriendList_Model::handle_FilePathinUserInfo(const QString& filePaht)
{
    emit relay_FilePathinUserInfo(filePaht);
}

/*  转发至UserInfo界面处理发送的文件Json信息
 *  sendingObj：文件Json信息
*/
int FriendList_Model::handle_SendingFileJsoninUserInfo(const QString& receiveFileObj, const QJsonObject& sendingObj)
{
    emit relay_SendingFileJsoninUserInfo(receiveFileObj,sendingObj);
}

//  转发至UserInfo界面处理发送的文件Json信息
void FriendList_Model::handle_RelayFileRequestinUserInfo()
{
    emit relay_FileRequestinUserInfo();
}
