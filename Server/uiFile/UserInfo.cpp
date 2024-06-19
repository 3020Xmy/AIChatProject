#include "UserInfo.h"
#include "ui_UserInfo.h"

UserInfo::UserInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserInfo)
{
    ui->setupUi(this);

    init_ModelView();   //初始化模型视图
}

UserInfo::~UserInfo()
{
    delete ui;
}

/*  初始化模型视图
*/
int UserInfo::init_ModelView()
{
    //初始化用户数据模型
    UserDataModel = new QStandardItemModel();

    //设置列名
    QStringList headerLabels;
    headerLabels << "IP地址" << "端口号" << "用户账号" << "当前操作";
    UserDataModel->setHorizontalHeaderLabels(headerLabels);

    //设置列的宽度为200像素
    ui->tableView->setColumnWidth(0, 600);
    ui->tableView->setColumnWidth(1, 600);
    ui->tableView->setColumnWidth(2, 600);
    ui->tableView->setColumnWidth(3, 600);

    ui->tableView->setWordWrap(false); // 文本过长不换行
    ui->tableView->setDragEnabled(false);    //设置禁止拖拽
    ui->tableView->setModel(UserDataModel);  //设置数据模型
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选择整行
    return 1;
}

/*  设置用户IP项
 *  id：视图Id    ip：替换的IP
*/
int UserInfo::set_IpItem(const int &id, const QString &ip)
{
    UserDataModel->item(id,0)->setText(ip);
    ui->tableView->update(); //视图更新
    return 1;
}

/*  设置连接的端口项
 *  id：视图Id    port：替换的端口
*/
int UserInfo::set_PortItem(const int& id,const QString& port)
{
    UserDataModel->item(id,1)->setText(port);
    ui->tableView->update(); //视图更新
    return 1;
}

/*  设置用户账号项
 *  id：视图Id    number：替换的账号
*/
int UserInfo::set_NumberItem(const int &id, const QString &number)
{
    UserDataModel->item(id,2)->setText(number);
    ui->tableView->update(); //视图更新
    return 1;
}

/*  设置操作类型项
 *  id：视图Id    type：替换的操作类型
*/
int UserInfo::set_TypeItem(const int &id, const QString &type)
{
    UserDataModel->item(id,3)->setText(type);
    ui->tableView->update(); //视图更新
    return 1;
}

/*  添加数据项
 *  ip：用户IPv4地址    port：链接端口    number：用户账号    type：用户当前操作
*/
int UserInfo::add_UserInfoItem(const QString& ip ,const QString& port,
                               const QString& number, const QString& type)
{
    UserDataModel->setItem(ItemSum,0,new QStandardItem(ip));
    UserDataModel->setItem(ItemSum,1,new QStandardItem(port));
    UserDataModel->setItem(ItemSum,2,new QStandardItem(number));
    UserDataModel->setItem(ItemSum,3,new QStandardItem(type));
    ui->tableView->show();  //显示视图
    return 1;
}

/*  新增数据项
 *  ip：用户IPv4地址    port：链接端口
*/
int UserInfo::add_NewUserInfoItem(const QString &ip, const QString &port)
{
    if(add_UserInfoItem(ip,port)){  //添加数据项
        emit return_UserItemId(port,ItemSum++);
    }
}
