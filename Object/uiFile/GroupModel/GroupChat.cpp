#include "GroupChat.h"
#include "ui_GroupChat.h"

GroupChat::GroupChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupChat)
{
    ui->setupUi(this);
}

GroupChat::GroupChat(const QString &name, const QString &id,
                     const QString &head_Path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupChat)
{
    ui->setupUi(this);

    //初始化对象
    group_id = id;           //群聊ID
    group_name = name;       //群聊昵称
    group_headimg = head_Path; //群聊头像

    //初始化界面
    init_GroupChatWidget(name,id,head_Path);
}

GroupChat::~GroupChat()
{
    delete ui;
}

////---------------------------------------事件模块函数------------------------------------------------------
/*  鼠标点击事件
 *  event：事件
*/
void GroupChat::mousePressEvent(QMouseEvent *event)
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
void GroupChat::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  鼠标移动事件
 *  event：事件
*/
void GroupChat::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

/*  获取群聊ID
 *  返回值：QString(群聊ID)
*/
QString GroupChat::get_GroupNumber()
{
    return group_id;
}

////---------------------------------------界面模块函数------------------------------------------------------
/*  初始化聊天界面
 *  name：群聊昵称    id：群聊Id    head_Path：群聊头像
*/
int GroupChat::init_GroupChatWidget(const QString &name, const QString &id, const QString &head_Path)
{
    setWindowFlags(Qt::WindowType::FramelessWindowHint);    //设置界面透明与去掉边框
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);   //设置listWidget关闭选中
    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); //设置listWidget为以像素大小进行移动

    ui->groupID->setText(id);         //初始化群聊Id
    ui->groupName_Lab->setText(name); //初始化群聊昵称
    QPixmap originalPixmap(head_Path);
    originalPixmap = originalPixmap.scaled(ui->headImage_Lab->width(),
                                           ui->headImage_Lab->height(), Qt::KeepAspectRatio);
    ui->headImage_Lab->setPixmap(originalPixmap);//初始化群聊头像

    //初始化样式表
    QFile file(":/new/qss/qssFile/scrollbar.qss");
    file.open(QFile::ReadOnly);
    ui->listWidget->verticalScrollBar()->setStyleSheet(file.readAll()); //设置listWidet对象样式
    return 1;
}

/*  处理项更新
 *  item：被替换的项    box：新的项
*/
int GroupChat::handle_NewChatItem(QListWidgetItem *item, ChatBox *box)
{
    ui->listWidget->setItemWidget(item,box);
    ui->input_Edit->clear(); //清空文本输入框
    ui->listWidget->setCurrentRow(ui->listWidget->model()->rowCount() - 1); //每次更新消息都显示最新的项
    return 1;
}

/*  最小化界面函数
*/
void GroupChat::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  Top关闭界面函数
*/
void GroupChat::on_close_Btn_clicked()
{
    this->close();
}

/*  Bottom关闭界面函数
*/
void GroupChat::on_close_Btnbottom_clicked()
{
    this->close();
}

/*  发送按钮
*/
void GroupChat::on_sending_Btn_clicked()
{
    Sendbox *send_item=new Sendbox(this);
    QListWidgetItem *item=new QListWidgetItem(ui->listWidget);  //初始化气泡
    send_item->handle_SendBoxShowText(ui->input_Edit->toPlainText());
    item->setSizeHint(QSize(200,send_item->return_SendBoxHeight()+50));
    send_item->handle_HeadImg(my_USER.get_UserInfo(USER::Headimg)); //设置头像
    emit handle_SendingGroupMessage(handle_SendingDataPackageAsJSON());   //请求发送消息
    handle_NewChatItem(item,send_item);
}

/*  处理接收的群聊消息
 *  message：消息    img：头像
*/
int GroupChat::handle_GroupMessage(const QString& message,const QString& img)
{
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);    //初始化气泡并输出
    Recvbox *recv_item = new Recvbox(this);
    recv_item->handle_RecvBoxShowText(message);
    recv_item->handle_HeadImg(img); //设置头像
    item->setSizeHint(QSize(250,recv_item->return_RecvBoxHeight()+50));
    handle_NewChatItem(item,recv_item);
    return 1;
}

/*  将发送的信息打包为Json模块
 *  返回值：QJsonObject(发送的Json信息)
*/
QJsonObject GroupChat::handle_SendingDataPackageAsJSON()
{
    QJsonObject Json;
    Json.insert("type","Sending_GroupData");
    QJsonObject dataObj;
    dataObj.insert("GroupNumber",group_id);
    dataObj.insert("Message",ui->input_Edit->toPlainText());
    dataObj.insert("sendingNumer",my_USER.get_UserInfo(USER::Number));
    dataObj.insert("sendingHead",my_USER.get_UserInfo(USER::Headimg));
    Json.insert("data",dataObj);
    return Json;
}

