#include "UserSetup.h"
#include "ui_UserSetup.h"

UserSetup::UserSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserSetup)
{
    ui->setupUi(this);

    //置控件信息
    set_AssemblyInfo();

    connect(&my_USER,&USER::new_USER,this,&UserSetup::new_WindowInfo);
}

UserSetup::~UserSetup()
{
    delete ui;
}

/*  设置控件信息
*/
int UserSetup::set_AssemblyInfo()
{
    //设置头像
    QString headimg_Css = QStringLiteral("QPushButton#headimg_Btn{"
                                         "border-image: url(%1);};").arg(my_USER.get_UserInfo(USER::Headimg));
    ui->headimg_Btn->setStyleSheet(headimg_Css);

    if(my_USER.get_UserInfo(USER::Sex) == "女"){ //设置性别
        ui->sex_Box->setItemText(0,"女");
        ui->sex_Box->setItemText(1,"男");
    }else{
        ui->sex_Box->setItemText(0,"男");
        ui->sex_Box->setItemText(1,"女");
    }
    ui->sex_Box->setCurrentIndex(0);

    ui->Number_Lab->setText(my_USER.get_UserInfo(USER::Number));    //设置账号
    ui->userName_Edit->setText(my_USER.get_UserInfo(USER::Name));   //设置昵称
    ui->userSign_Edit->setText(my_USER.get_UserInfo(USER::Sign));   //设置个性签名
    return 1;
}

/*  更新控件消息
*/
int UserSetup::new_WindowInfo()
{
    if(set_AssemblyInfo()){
        return 1;
    }
    return 0;
}

/*  确定修改信息
*/
int UserSetup::on_determine_Btn_clicked()
{
    my_USER.set_AllObject(ui->sex_Box->currentText(),ui->userName_Edit->text(),ui->userSign_Edit->text(),
                          ui->Number_Lab->text(),my_USER.get_UserInfo(USER::Headimg));


    QMessageBox::information(nullptr,"提示","用户信息设置成功",QMessageBox::Ok);
    return 1;
}

