#ifndef USERINFO_H
#define USERINFO_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QStandardItemModel>

namespace Ui {
class UserInfo;
}

class UserInfo : public QWidget
{
    Q_OBJECT

public:
    explicit UserInfo(QWidget *parent = nullptr);
    ~UserInfo();

public:
    //初始化模型视图
    int init_ModelView();
    //设置用户IP项
    int set_IpItem(const int& id, const QString& ip);
    //设置连接的端口项
    int set_PortItem(const int& id,const QString& port);
    //设置用户账号项
    int set_NumberItem(const int& id, const QString& number);
    //设置操作类型项
    int set_TypeItem(const int& id, const QString &type);
    //添加数据项
    int add_UserInfoItem(const QString& ip ,const QString& port,
                         const QString& number = " ", const QString& type = " ");
public slots:
    //新增数据项
    int add_NewUserInfoItem(const QString& ip ,const QString& port);
signals:
    //返回用户项Id
    void return_UserItemId(const QString& port, const int& ItemId);
private:
    int ItemSum = 0; //项的总个数
    Ui::UserInfo *ui;
    QStandardItemModel *UserDataModel;  //用户数据模型
};

#endif // USERINFO_H
