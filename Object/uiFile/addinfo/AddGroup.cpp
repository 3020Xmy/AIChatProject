#include "AddGroup.h"
#include "ui_AddGroup.h"

AddGroup::AddGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddGroup)
{
    ui->setupUi(this);
}

AddGroup::~AddGroup()
{
    delete ui;
}

/*  设置界面查找的群聊信息
 *  number：群聊账号    name：群聊昵称    headimg_Path：群聊头像
*/
int AddGroup::set_AddGroupWindow(const QString &number, const QString &name, const QString &headimg_Path)
{
    //设置群聊信息
    ui->name_text->setText(name);
    ui->group_Number->setText(number);
    QPixmap headimg(headimg_Path);  //设置群聊头像
    ui->groupImg->setPixmap(headimg);
    return 1;
}
