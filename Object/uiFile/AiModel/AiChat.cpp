#include "AiChat.h"
#include "ui_AiChat.h"

AiChat::AiChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AiChat)
{
    ui->setupUi(this);

    //初始化界面
    init_AiChatWidgte();
}

AiChat::~AiChat()
{
    delete ui;
}

////------------------------------------事件模块函数-------------------------------------------------------------
/*  鼠标点击事件
 *  event：事件
*/
void AiChat::mousePressEvent(QMouseEvent *event)
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
void AiChat::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}


/*  鼠标移动事件
 *  event：事件
*/
void AiChat::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

////------------------------------------界面模块函数-------------------------------------------------------------
/*  初始化界面
*/
int AiChat::init_AiChatWidgte()
{
    ui->FriendHead->setScaledContents(true);    //设置头像大小自适应
    setWindowFlags(Qt::WindowType::FramelessWindowHint);    //设置界面透明与去掉边框
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);   //设置listWidget关闭选中
    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);   //设置listWidget属性为以像素大小进行移动

    //设置listWidet对象样式
    QFile file(":/new/qss/qssFile/scrollbar.qss");
    file.open(QFile::ReadOnly);
    ui->listWidget->verticalScrollBar()->setStyleSheet(file.readAll());

    //当Ai信息发生改变后更新聊天界面Ai信息
    connect(&my_AI, AI::new_AIInfo,this,AiChat::new_AiChatWidgetInfo);
}

/*  消息发送按钮
*/
void AiChat::on_sending_Btn_clicked()
{
    QString text = ui->text_Edit->toPlainText();    //获取输入的文本

    //初始化气泡并输出
    QListWidgetItem *item=new QListWidgetItem(ui->listWidget);
    Sendbox* send_item=new Sendbox(this);
    send_item->handle_SendBoxShowText(ui->text_Edit->toPlainText());
    item->setSizeHint(QSize(250,send_item->return_SendBoxHeight()+50));
    ui->listWidget->setItemWidget(item,send_item);
    send_item->handle_HeadImg(my_USER.get_UserInfo(USER::Headimg));

    ui->text_Edit->clear(); //清空文本输入框

    //每次更新消息都显示最新的项
    ui->listWidget->setCurrentRow(ui->listWidget->model()->rowCount() - 1);

    //设置文本并启动线程
    if(my_NETWORK.handle_InspectKeyandSecret()){
        ai_Thread = new AiThread(my_NETWORK.handle_SetEnquireText(text));
        connect(ai_Thread,&AiThread::getAnswer,this,&AiChat::get_Aianswer);     //处理Ai答复后数据
        QThreadPool::globalInstance()->start(ai_Thread);
    }
}

/*  处理消息回复
 *  response：回复的消息文本
*/
int AiChat::get_Aianswer(const QString &response)
{
    //初始化气泡并输出
    QListWidgetItem *item=new QListWidgetItem(ui->listWidget);
    Recvbox* recv_Item=new Recvbox(this);
    recv_Item->handle_RecvBoxShowText(response);
    item->setSizeHint(QSize(250,recv_Item->return_RecvBoxHeight()+50));
    ui->listWidget->setItemWidget(item,recv_Item);

    //每次更新消息都显示最新的项
    ui->listWidget->setCurrentRow(ui->listWidget->model()->rowCount() - 1);
    return 1;
}

/*  设置窗口消息
*/
int AiChat::new_AiChatWidgetInfo()
{
    //设置参数
    ui->FriendName->setText(my_AI.handle_GetAiInfo(AI::aiName));
    ui->FriendSign->setText(my_AI.handle_GetAiInfo(AI::aiSign));
    return 1;
}

/*  最小化界面函数
*/
void AiChat::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  Top关闭界面函数
*/
void AiChat::on_close_Btntop_clicked()
{
    this->close();
}

/*  Bottom关闭界面函数
*/
void AiChat::on_close_Btnbottom_clicked()
{
    this->close();
}

////------------------------------------Ai模块函数-------------------------------------------------------------
/*  设置机器人信息
 *  headPath：头像路径   name：好友昵称   sign：好友个性签名
*/
int AiChat::set_AiChatinAiInfo(const QString &headPath,const QString &name,const QString &sign)
{
    //设置头像
    QPixmap Img(headPath);
    Img = Img.scaled(ui->FriendHead->width(),
                     ui->FriendHead->height(), Qt::KeepAspectRatio);
    ui->FriendHead->setPixmap(Img);

    //设置昵称
    ui->FriendName->setText(my_AI.handle_GetAiInfo(AI::aiName));
    //设置好友个性签名
    ui->FriendSign->setText(my_AI.handle_GetAiInfo(AI::aiSign));
}





