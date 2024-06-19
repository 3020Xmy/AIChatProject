#include "AddInfo.h"
#include "ui_AddInfo.h"

AddInfo::AddInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddInfo)
{
    ui->setupUi(this);

    //初始化界面
    init_Widget();
}

AddInfo::~AddInfo()
{
    delete ui;
}

////------------------------------------界面控件函数--------------------------------------------------------------
/*  初始化界面
*/
int AddInfo::init_Widget()
{
    //初始化对象
    group_Ok = false;
    friend_Ok = false;
    AddGroup_GUI = nullptr;
    AddFriend_GUI = nullptr;

    setWindowFlags(Qt::WindowType::FramelessWindowHint);    //去掉边框
    ui->textEdit->setDisabled(true);

    //设置Top中的gif动画
    QMovie *back_Gif = new QMovie(this);
    back_Gif->setFileName(":/new/logo/icons/logo/addWidget.gif");
    back_Gif->start();
    ui->back_Img->setMovie( back_Gif);

    //初始化输入验证器，限制输入为数值
    usernumber_Validator = new QRegularExpressionValidator(QRegularExpression("\\d{10}"), this);
    groupnumber_Validator = new QRegularExpressionValidator(QRegularExpression("\\d{8}"), this);
    return 1;
}

/*  确定添加函数
*/
void AddInfo::on_add_Btn_clicked()
{
    if(friend_Ok){
        //确定添加好友信息
        friend_Number = ui->textEdit->text();
        if(AddFriend_GUI->get_State()){
            QMessageBox::information(nullptr,"提示","已申请好友验证，请稍后...",QMessageBox::Ok);
            emit request_ApplyForFriendVerify("applyForfriendVerify",friend_Number);     //请求服务器处理请求好友验证
        }
        else{
            QMessageBox::information(nullptr,"提示","当前好友未在线",QMessageBox::Ok);
        }
    }
    else if(group_Ok){
        //确定添加群聊信息
        group_Number  = ui->textEdit->text();
        emit request_ApplyForGroupVerify("applyForgroupVerify",group_Number);     //请求服务器处理请求群聊验证
    }
}

/*  关闭界面
*/
void AddInfo::on_clos_Widget_clicked()
{
    this->close();
}

/*  设置提示信息
*/
int AddInfo::set_TipText(const QString& text)
{
    ui->info_label->setText(text);
    return 1;
}

/*  添加好友按钮
 *  返回值：void
*/
void AddInfo::on_add_Friend_clicked()
{
    group_Ok = false;
    friend_Ok = true;
    if(AddGroup_GUI != nullptr){
        delete AddGroup_GUI;   //防止内存泄漏
        AddGroup_GUI = nullptr;
    }
    ui->textEdit->setEnabled(true);
    ui->textEdit->setValidator(usernumber_Validator);
    set_TipText("请输入好友账号");     //设置提示信息
}

/*  添加群聊按钮
*/
void AddInfo::on_add_Group_clicked()
{
    group_Ok = true;
    friend_Ok = false;
    if(AddFriend_GUI != nullptr){
        delete AddFriend_GUI;   //防止内存泄漏
        AddFriend_GUI = nullptr;
    }
    ui->textEdit->setEnabled(true);
    ui->textEdit->setValidator(groupnumber_Validator);
    set_TipText("请输入群聊账号");     //设置提示信息
}

/*  确定查找按钮
*/
void AddInfo::on_ok_Btn_clicked()
{
    if(friend_Ok){  //添加好友
        friend_Number = ui->textEdit->text();
        emit get_AddFriendInfo("selectFriend",friend_Number);
    }
    else if(group_Ok){  //添加群聊
        group_Number = ui->textEdit->text();
        emit get_AddGroupInfo("selectGroup",group_Number);
    }
    else{
        QMessageBox::information(nullptr,"提示","查找好友或群聊选项未点击",QMessageBox::Ok);
    }
}

////------------------------------------添加好友模块函数--------------------------------------------------------------
/*  将好友信息显示到组件中
 *  code：错误码    name：查询的好友昵称    state：查询的好友状态    sex：查询的好友性别    sign：查询的好友个签
 *  number：查询的好友账号    headimg_Path：查询的好友头像
*/
int AddInfo::handle_FriendInfoinWidget(const QString& code,const QString& state,const QString &name,
                                       const QString &sex,const QString &sign,const QString &number,
                                       const QString &headimg_Path)
{
    if(code == "61"){
        if(AddFriend_GUI != nullptr){
            delete AddFriend_GUI;   //防止内存泄漏
            AddFriend_GUI = nullptr;
        }
        AddFriend_GUI = new AddFriend(ui->info_Widget);     //创建好友信息界面
        AddFriend_GUI->set_AddFriendWindow(state,name,sex,sign,number,headimg_Path);
        AddFriend_GUI->show();
    }else{
        QMessageBox::information(nullptr,"提示","查询失败，信息码：62！",QMessageBox::Ok);
    }
    return 1;
}

////------------------------------------添加群聊模块函数--------------------------------------------------------------
/*  将群聊信息显示到组件中
 *  code：错误码    number：查询的群聊号码    name：查询的群聊昵称    headimg_Path：查询的群聊头像
*/
int AddInfo::handle_GroupInfoinWidget(const QString &code, const QString &number,
                                      const QString &name, const QString &headimg_Path)
{
    if(code == "91"){
         if(AddGroup_GUI != nullptr){
            delete AddGroup_GUI;   //防止内存泄漏
            AddGroup_GUI = nullptr;
         }
         AddGroup_GUI = new AddGroup(ui->info_Widget);     //创建群聊信息界面
         AddGroup_GUI->set_AddGroupWindow(number,name,headimg_Path);
         AddGroup_GUI->show();
    }else{
         QMessageBox::information(nullptr,"提示","查询失败，信息码：92！",QMessageBox::Ok);
    }
    return 1;
}

////------------------------------------事件模块函数--------------------------------------------------------------
/*  鼠标点击事件
 *  event：事件
*/
void AddInfo::mousePressEvent(QMouseEvent *event)
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
void AddInfo::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  鼠标移动事件
 *  event：事件
*/
void AddInfo::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

