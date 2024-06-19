#ifndef ADDVERIFY_H
#define ADDVERIFY_H

#include <QWidget>
#include <QJsonObject>
#include "AddFriend.h"
#include "srcFile/USER.h"

namespace Ui {
class AddVerify;
}

class AddVerify : public QWidget
{
    Q_OBJECT

public:
    ~AddVerify();
    explicit AddVerify(QWidget *parent = nullptr);

////------------------------------------界面模块函数-----------------------------------------------------
public:
    //初始化界面
    int init_Window();
    //设置界面信息
    int set_AddVerifyWindow(const QString &type,const QString &name, const QString &sex,
                            const QString &sign,const QString &number, const QString &headimg_Path);
private slots:
    //确定按钮
    void on_pushButton_clicked();
    //否定按钮
    void on_pushButton_2_clicked();
////------------------------------------添加好友模块函数-----------------------------------------------------
signals:
    //返回验证结果
    void return_VerifyResult(const QJsonObject &jsondata);
////------------------------------------添加群聊模块函数-----------------------------------------------------

private:
    Ui::AddVerify *ui;
    QString operator_Type;      //操作类型
    QString friend_Number;      //好友账号
    AddFriend *AddFriend_GUI;   //好友信息窗口
};

#endif // ADDVERIFY_H
