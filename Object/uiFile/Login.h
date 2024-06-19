#ifndef LOGIN_H
#define LOGIN_H

#include <QTimer>
#include <QMovie>
#include <QWidget>
#include <QPainter>
#include <QHostInfo>
#include <QSettings>
#include "UserInfo.h"
#include "Register.h"
#include <QMouseEvent>
#include "SetUp/SetUp.h"
#include "srcFile/USER.h"
#include <QPropertyAnimation>
#include "srcFile/TcpThread.h"
#include <QRegularExpressionValidator>

class QPropertyAnimation;

namespace Ui {
class Login;
}

//登录界面类
class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
////-------------------------------------------Tcp模块函数---------------------------------------------------
public:
    //初始化Tcp模块
    int init_TcpModule();
    //初始化Tcp线程连接
    int init_TcpConnect();
    //启动线程
    int handle_StartTcpThread();
////-------------------------------------------登录模块函数---------------------------------------------------
private slots:
    //登录验证
    void on_logon_Btn_clicked();
public:
    //将登录数据打包为Json格式
    int handle_LoginRequestPackageAsJSON();
public slots:
    //请求UserInfo界面初始化群聊界面
    int request_InitGroupInfoWidget(const QString &name,const QString &id,const QString headimg);
    //请求UserInfo界面初始化好友界面
    int request_InitFriendInfoWidget(const QString &name, const QString &sign, const QString &number,
                                     const QString headimg, const QString &state);
    //初始化用户界面
    int handle_InitUserInfoWidget(bool ok, const QString &code, const QString &sex, const QString &name,
                                  const QString &sign, const QString &number, const QString headimg);
/////-------------------------------------------加密模块函数---------------------------------------------------
public:
    //将加密数据打包为Json格式
    int handle_EncryptPackageAsJSON();
public slots:
    //获取加密后的数据
    int get_EncryptData(const QString &str);
    //处理加密请求返回的结果
    int handle_EncryptResult(const bool &ok,const QString &code);
private slots:
    //记住账号
    void on_saved_number_clicked(bool checked);
    //记住密码
    void on_saved_Password_clicked(bool checked);
////-------------------------------------------注册模块函数----------------------------------------------------
private slots:
    //注册账号
    void on_register_Btn_clicked();
public:
    //验证账号密码输入是否正确
    bool handle_InputResult();
    //将注册数据打包为Json格式
    int handle_RegisterPackageAsJSON(QString name, QString number, QString sex, QString password, QString path);
public slots:
    //转发注册结果至Login界面
    void relay_RegisterResult(bool ok);
signals:
    //请求Login界面处理注册结果
    void request_LoginHandleRegisterResult(bool ok);
////-------------------------------------------应用配置函数----------------------------------------------------
public:
    //读取设置文件
    int get_Settings();
    //修改设置文件
    int set_Settings();
    //初始化默认配置
    int init_Settings();
////-------------------------------------------界面控件函数----------------------------------------------------
private slots:
    //界面关闭
    void on_clos_Btn_clicked();
    //界面缩小
    void on_reduce_Btn_clicked();
public:
    //初始化界面
    int init_LoginWidget();
    //绘制登录动画，显示用户信息界面
    int set_Animation(const QString& headimg);
    //设置用户头像
    int init_UserHeadImg(const QString& headimg);
public slots:
    //处理等待动画后再显示界面
    int handle_closeWidget();
    //显示Login界面
    int handle_ShowLoginWidget();
    //显示UserInfo界面
    int handle_ShowUserInfoWidget();
signals:
    //请求关闭线程
    void handle_TcpThreadClose(const QString& number);
////-------------------------------------------事件模块函数----------------------------------------------------
protected:
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
////-----------------------------------------------变量-------------------------------------------------------
private:
    Ui::Login *ui;
    bool move_Ok;           //是否移动
    QString localIPv4;      //IPv4地址
    QPoint move_point;      //移动的距离
    QSettings *settings;    //配置文件
    bool saved_Password;    //是否记住密码
    bool saved_Usernumbe;   //是否记住账号
    TcpThread *tcpThread_Obj; //数据处理线程
    Register* Register_GUI;   //注册界面
    UserInfo *UserInfo_GUI;   //用户信息界面
    QPropertyAnimation *animation;  //登录动画
    QRegularExpressionValidator *usernumber_Validator;    //号码输入验证器
    QRegularExpressionValidator *password_Validator;      //密码输入验证器

private:
    QString input_Password;         //输入的密码
    QString input_Usernumber;       //输入的账号
    QString encrypt_Password;       //加密的密码

    //接收注册的变量
    QString register_Sex;           //注册用户的性别
    QString register_Name;          //注册用户的昵称
    QString register_Number;        //注册用户的账号
    QString register_Headimg;       //注册用户的头像
    QString register_Password;      //注册用户的密码
};

#endif // LOGIN_H
