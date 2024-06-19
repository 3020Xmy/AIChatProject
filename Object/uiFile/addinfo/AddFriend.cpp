#include "AddFriend.h"
#include "ui_AddFriend.h"

AddFriend::AddFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);

    //初始化界面
    init_Window();
}

AddFriend::~AddFriend()
{
    delete ui;
}

/*  初始化界面
*/
int AddFriend::init_Window()
{
    //去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);
    return 1;
}

/*  设置界面查找的好友信息
 *  state：好友状态    name：好友昵称    sex：好友性别    sign：好友个签    number：好友账号    headimg_Path：好友头像
*/
int AddFriend::set_AddFriendWindow(const QString& state,const QString &name, const QString &sex,
                                   const QString& sign, const QString &number, const QString &headimg_Path)
{
    //设置好友信息
    ui->sex->setText(sex);
    ui->name->setText(name);
    ui->name_2->setText(sign);
    ui->numbear->setText(number);
    QPixmap headimg(headimg_Path);  //设置好友头像
    ui->Headimg->setPixmap(headimg);

    if(state == "1"){   //设置头像状态样式
        ui->Headimg->setStyleSheet("border: 2px solid green;");
    }
    else{
        ui->Headimg->setStyleSheet("border: 2px solid black;");
    }
    Friend_State = state;
    return 1;
}

/*  获取好友的状态
 *  返回值：bool(在线True，离线False)
*/
bool AddFriend::get_State()
{
    if(Friend_State == "1"){
        return true;
    }
    else{
        return false;
    }

}
