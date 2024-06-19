#include "GroupList_Model.h"

GroupList_Model::GroupList_Model(QWidget *parent)
    :QToolBox(parent)
{
    //初始化对象
    len = 0;
    handle_AddGroupList("加入的群聊");
}

GroupList_Model::~GroupList_Model()
{

}

/*  新增群组
 *  name：名字    id：群聊ID    head_Path：头像路径
*/
int GroupList_Model::handle_AddGroup(const QString &name,const QString &id,
                                                        const QString &head_Path)
{
    GroupInfo* Demo = new GroupInfo(name,id,head_Path);
    QSharedPointer<GroupInfo> info_Demo(Demo);  //使用智能指针托管
    GroupInfo_Vector.append(info_Demo);
    handle_GroupInsertList(ListWidget_Vector[0],GroupInfo_Vector[len]);
    ++len;

    //转发至UserInfo界面处理发送的信息
    connect(Demo,&GroupInfo::relay_GroupMessageinModel,this,GroupList_Model::handle_GroupMessageinUserInfo);
    return 1;
}

/*  转发至UserInfo界面处理发送的信息
 *  sendingObj：发送的消息
*/
int GroupList_Model::handle_GroupMessageinUserInfo(const QJsonObject &sendingObj)
{
    emit relay_GroupMessageinUserInfo(sendingObj);
    return 1;
}

/*  转发至GroupInfo界面处理发送的信息
 *  jsonObject：消息
*/
int GroupList_Model::request_MessageToGroupInfo(const QJsonObject& jsonObject)
{

    for(int i = 0; i<len ;++i){
        GroupInfo_Vector[i].data()->request_MessageToGroupChat(jsonObject);
    }
    return 1;
}

/*  新增分组
 *  name：分组名称
*/
int GroupList_Model::handle_AddGroupList(const QString &name)
{
    QSharedPointer<QListWidget> Demo(new QListWidget);   //使用智能指针托管
    ListWidget_Vector.append(Demo);
    this->addItem(Demo.data(),name);
    return 1;
}

/*  群组插入分组
 *  List：指定分组容器   Group：指定好友容器
*/
int GroupList_Model::handle_GroupInsertList(QSharedPointer<QListWidget> &List,
                                            QSharedPointer<GroupInfo> &Group)
{
    QListWidgetItem *Item = new QListWidgetItem();//新建替换的Item
    Item->setSizeHint(QSize(270, 30));
    List->addItem(Item);                          //分组中添加Item
    List->setItemWidget(Item, Group.data());      //修改Item为自定义样式(GroupInfo)
    return 1;
}

