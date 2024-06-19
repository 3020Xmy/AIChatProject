#include "AiList_Model.h"

AiList_Model::~AiList_Model()
{

}

AiList_Model::AiList_Model(QWidget *parent)
    :QToolBox(parent)
{
    handle_AddAiMessage();
    handle_AddAiList("当前机器人");
    handle_MessageInsertlist(ListWidget_Vector[0],MessageInfo_Vector[0]);
}

/*  新增消息
 *  name：名字    message：消息   head_Path：头像路径    timer：时间
*/
int AiList_Model::handle_AddAiMessage()
{
    QSharedPointer<AiInfo> Demo(new AiInfo()); //使用智能指针托管
    MessageInfo_Vector.append(Demo);
    return 1;
}

/*  新增机器人分组
 *  name：分组名称
*/
int AiList_Model::handle_AddAiList(const QString &name)
{
    QSharedPointer<QListWidget> Demo(new QListWidget);   //使用智能指针托管
    ListWidget_Vector.append(Demo);
    this->addItem(Demo.data(),name);
    return 1;
}

/*  将机器人插入分组
 *  List：指定分组容器   Message：指定消息容器
*/
int AiList_Model::handle_MessageInsertlist(QSharedPointer<QListWidget> &List,
                                           QSharedPointer<AiInfo> &Message)
{
    QListWidgetItem *item = new QListWidgetItem();  //新建替换的Item
    item->setSizeHint(QSize(270, 65));
    List->addItem(item);                            //分组中添加Item
    List->setItemWidget(item, Message.data());      //修改Item为自定义样式(Message)
    return 1;
}
