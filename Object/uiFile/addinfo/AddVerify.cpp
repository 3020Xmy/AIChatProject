#include "AddVerify.h"
#include "ui_AddVerify.h"

AddVerify::AddVerify(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddVerify)
{
    ui->setupUi(this);

    //初始化界面
    init_Window();
}

AddVerify::~AddVerify()
{
    delete AddFriend_GUI;
    delete ui;
}

////----------------------------------------界面模块函数---------------------------------------------------------
/*  初始化界面
*/
int AddVerify::init_Window()
{
    //初始化对象
    operator_Type = " ";
    friend_Number = " ";
    AddFriend_GUI = nullptr;
    setWindowFlags(Qt::WindowType::FramelessWindowHint);    //去掉边框
    return 1;
}

/*  设置界面信息
*/
int AddVerify::set_AddVerifyWindow(const QString &type, const QString &name, const QString &sex,
                                   const QString &sign, const QString &number, const QString &headimg_Path)
{
    operator_Type = type;
    if(operator_Type  == "friend"){
        if(AddFriend_GUI != nullptr){
            delete AddFriend_GUI;
        }
        friend_Number = number;
        AddFriend_GUI = new AddFriend(ui->bottom_Widget);
        AddFriend_GUI->set_AddFriendWindow("1",name,sex,sign,number,headimg_Path);
        AddFriend_GUI->show();
    }
    return 1;
}

/*  否定按钮
*/
void AddVerify::on_pushButton_2_clicked()
{
    if(operator_Type == "friend"){
        QJsonObject Json;
        Json.insert("type","addfriendResult");
        QJsonObject dataObj;
        dataObj.insert("userNumber",my_USER.get_UserInfo(USER::Number));
        dataObj.insert("friendNumber",friend_Number);
        Json.insert("data",dataObj);
        emit return_VerifyResult(Json);   //返回拒绝好友结果
    }
    this->close();
}


/*  确定按钮
*/
void AddVerify::on_pushButton_clicked()
{
    if(operator_Type == "friend"){
        QJsonObject Json;
        Json.insert("type","addfriendResult");
        QJsonObject dataObj;
        dataObj.insert("userNumber",my_USER.get_UserInfo(USER::Number));
        dataObj.insert("friendNumber",friend_Number);
        Json.insert("data",dataObj);
        emit return_VerifyResult(Json);   //返回同意好友结果
    }
    this->close();
}

