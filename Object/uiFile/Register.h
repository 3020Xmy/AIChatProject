#ifndef REGISTER_H
#define REGISTER_H

#include <QMovie>
#include <QWidget>
#include "HeadImg.h"
#include <QTcpSocket>
#include <QMessageBox>
#include <QMouseEvent>
#include <QIntValidator>
#include "srcFile/TcpThread.h"
#include <QRegularExpressionValidator>

class QRegularExpressionValidator;
class Login;

namespace Ui {
    class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
////-------------------------------------------注册模块函数----------------------------------------------------
private slots:
    //请求注册
    void on_register_Btn_clicked();
public slots:
    //处理注册结果
    int handle_RegisterResult(bool ok);
public:
    //检测用户输入是否合理
    bool handle_getInputSecure();
signals:
    //请求Login界面处理申请注册信息
    void requesr_LoginHandleRegister(QString name, QString number, QString sex, QString password, QString path);
////-------------------------------------------界面控件函数----------------------------------------------------
signals:
    //显示登录界面
    void handle_LoginShow();
public:
    //初始化界面
    int init_RegisterWidget();
private slots:
    //关闭界面函数
    void on_clos_Btn_clicked();
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //选择头像函数
    void on_headimg_Btn_clicked();
public slots:
    //显示选择头像界面
    int handle_ShowHeadImg(QString path);
////-------------------------------------------事件模块函数----------------------------------------------------
protected:
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::Register *ui;
    bool move_Ok;        //是否移动
    QPoint move_point;   //移动的距离
    bool tcp_Ok = false;         //是否连接上服务端
    HeadImg *HeadImg_GUI;        //选择头像界面
    QRegularExpressionValidator *number_Validator;    //号码输入验证器
    QRegularExpressionValidator *password_Validator;  //密码输入验证器

private:
    QString input_Sex;           //输入的性别
    QString input_Name;          //输入的名字
    QString input_Head;          //选择的头像
    QString input_Number;        //输入的号码
    QString input_Password;      //输入的密码
};

#endif // REGISTER_H
