#include "GroupInfo.h"
#include "ui_GroupInfo.h"

GroupInfo::GroupInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupInfo)
{
    ui->setupUi(this);
}

GroupInfo::GroupInfo(const QString &name, const QString &id,
                     const QString &head_Path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupInfo)
{
    ui->setupUi(this);

    //初始化界面
    init_GroupInfoWidget(name,id,head_Path);
}


GroupInfo::~GroupInfo()
{
    delete ui;
}

////---------------------------------------事件操作函数-------------------------------------------------------
/*  鼠标双击事件
 *  event：事件
*/
void GroupInfo::mouseDoubleClickEvent(QMouseEvent *event)
{
    Chat.data()->show();
    event->accept();
}

////---------------------------------------界面操作函数--------------------------------------------------------
/*  初始化群聊信息界面
 *  name：群聊昵称    id：群聊ID    head_Path：群聊头像
*/
int GroupInfo::init_GroupInfoWidget(const QString &name, const QString &id, const QString &head_Path)
{
    //初始化参数
    Chat = QSharedPointer<GroupChat>(new GroupChat(name,id,head_Path));
    //转发至GroupList_Model处理发送的文件
    connect(Chat.data(),&GroupChat::handle_SendingGroupMessage,this,&GroupInfo::relay_SendingGroupMessage);

    //设置头像大小自适应
    ui->Image->setScaledContents(true);

    //初始化姓名，个性签名，头像
    ui->groupName_Lab->setText(name);
    QPixmap originalPixmap(head_Path);
    originalPixmap = originalPixmap.scaled(ui->Image->width(),
                                           ui->Image->height(), Qt::KeepAspectRatio);
    ui->Image->setPixmap(originalPixmap);
    return 1;
}

/*  转发至GroupList_Model处理发送的信息
 *  sendingObj：发送的Json信息
*/
int GroupInfo::relay_SendingGroupMessage(const QJsonObject& sendingObj)
{
    emit relay_GroupMessageinModel(sendingObj);
    return 1;
}

/*  处理群聊信息
 *  jsonObject：消息
*/
int GroupInfo::request_MessageToGroupChat(const QJsonObject& jsonObject)
{
    if(Chat.data()->get_GroupNumber() == jsonObject["GroupNumber"].toString()){
        Chat.data()->show();
        Chat.data()->handle_GroupMessage(jsonObject["Message"].toString(),jsonObject["sendingHead"].toString());
        return 1;
    }else{
        return 0;
    }
}
