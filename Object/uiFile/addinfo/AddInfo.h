#ifndef ADDINFO_H
#define ADDINFO_H

#include <QPoint>
#include <QMovie>
#include <QWidget>
#include "AddGroup.h"
#include "AddFriend.h"
#include <QMouseEvent>
#include <QMessageBox>
#include <QRegularExpressionValidator>

namespace Ui {
class AddInfo;
}

class AddInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AddInfo(QWidget *parent = nullptr);
    ~AddInfo();

////------------------------------------添加好友模块函数-----------------------------------------------------
public slots:
    //将好友信息显示到组件中
    int handle_FriendInfoinWidget(const QString& code,const QString& state, const QString &name,
                                  const QString &sex,const QString &sign, const QString &number,
                                  const QString &headimg_Path);
private slots:
    //确定添加好友按钮
    void on_add_Btn_clicked();
    //添加好友按钮
    void on_add_Friend_clicked();
signals:
    //请求服务器获取添加好友的信息
    void get_AddFriendInfo(const QString& type,const QString number);
    //请求服务器处理请求好友验证
    void request_ApplyForFriendVerify(const QString& type, const QString &number);
////------------------------------------添加群聊模块函数-----------------------------------------------------
public slots:
    //将群聊信息显示到组件中
    int handle_GroupInfoinWidget(const QString& code, const QString &number,
                                 const QString &name, const QString &headimg_Path);
private slots:
    //确定查找按钮
    void on_ok_Btn_clicked();
    //添加群聊按钮
    void on_add_Group_clicked();
signals:
    //请求服务器获取添加群聊信息
    void get_AddGroupInfo(const QString& type,const QString number);
    //请求服务器处理请求群聊验证
    void request_ApplyForGroupVerify(const QString& type, const QString &number);
////------------------------------------界面控件函数--------------------------------------------------------
public:
    //初始化界面
    int init_Widget();
    //设置提示信息
    int set_TipText(const QString& text);
private slots:
    //关闭界面
    void on_clos_Widget_clicked();
////------------------------------------事件模块函数--------------------------------------------------------
protected:
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::AddInfo *ui;
    bool move_Ok;       //是否移动
    bool group_Ok;      //是否查找群聊
    bool friend_Ok;     //是否查找好友
    QPoint move_point;  //移动的距离
    AddGroup *AddGroup_GUI;    //添加的群聊信息界面
    AddFriend *AddFriend_GUI;    //添加的好友信息界面
    QRegularExpressionValidator *usernumber_Validator;    //用户账号输入验证器
    QRegularExpressionValidator *groupnumber_Validator;   //群聊账号输入验证器

private:
    QString group_Number;       //查找的群聊账号
    QString friend_Number;      //查找的好友账号
};

#endif // ADDINFO_H
