#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QPoint>
#include <QWidget>
#include "SqlInfo.h"
#include <QTcpSocket>
#include <QTcpServer>
#include "FileInfo.h"
#include "UserInfo.h"
#include "GroupInfo.h"
#include <QMouseEvent>
#include <QThreadPool>
#include <QJsonObject>
#include "srcFile/tcpThread/TcpThread.h"
#include "srcFile/sqlThread/SqlThread.h"

namespace Ui {
class mainWidget;
}

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

////--------------------------------------文件发送模块函数---------------------------------------------------
public slots:
    //处理转发的文件Json数据
    void handle_FriendSendingFileJson(const QString& number, const QString& path, const QJsonObject& imgJson);
signals:
    //请求Tcp向客户端发送文件Json数据
    void reques_FriendFileJsonToClient(const QString& number, const QString& path, const QJsonObject &imgJson);
////--------------------------------------表情发送模块函数---------------------------------------------------
public slots:
    //处理转发的好友消息
    int handle_FriendSendingEmotion(const QString &sending,const QString &receive,const QString &message);
signals:
    //请求Tcp向客户端发送好友消息
    void reques_FriendEmotionToClient(const QString &receiveid,QJsonObject rootObj);
////--------------------------------------消息发送模块函数---------------------------------------------------
public slots:
    //处理转发的群聊消息
    void handle_GroupSendingMessage(QJsonObject dataObject);
    //处理转发的好友消息
    int handle_FriendSendingMessage(const QString &sending,const QString &receive,const QString &message);
signals:
    //请求Tcp向客户端发送群聊消息
    void reques_GroupMessageToClient(QJsonObject dataObject);
    //请求Tcp向客户端发送好友消息
    void reques_FriendMessageToClient(const QString &receiveid,QJsonObject rootObj);
////--------------------------------------Tcp模块函数---------------------------------------------------
public:
    //获取本机IPV4地址
    int get_LocalIPv4();
    //初始化Tcp模块
    int init_TcpModule();
    //初始化Tcp链接
    int init_TcpConnection();
////--------------------------------------Sql模块函数---------------------------------------------------
public:
    //初始化数据库模块
    int init_SqlModule();
////--------------------------------------事件模块函数---------------------------------------------------
protected:
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
////--------------------------------------界面模块函数---------------------------------------------------
public:
    //初始化界面
    int init_MainWidget();
private slots:
    //关闭窗口函数
    void on_clos_Btn_clicked();
    //缩小窗口函数
    void on_reduce_Btn_clicked();
    //数据库信息窗口
    void on_sqlinfo_But_clicked();
    //文件转发信息窗口
    void on_fileinfo_But_clicked();
    //用户信息按钮
    void on_userinfo_But_clicked();
    //群聊信息窗口
    void on_groupinfo_But_clicked();
signals:
    //请求所有线程
    void request_Disconnect();

private:
    Ui::mainWidget *ui;
    bool move_Ok;         //是否移动
    QPoint move_point;    //移动的距离
    SqlInfo *SqlInfo_GUI;       //数据库信息窗口
    QTcpServer *tcpServer;      //TCP服务器
    TcpThread *tcp_Thread;      //Tcp线程，获取客户端信息
    SqlThread *sql_Thread;      //Sql线程，获取数据库信息
    FileInfo *FileInfo_GUI;     //文件信息窗口
    UserInfo *UserInfo_GUI;     //用户信息窗口
    GroupInfo *GroupInfo_GUI;   //群聊信息窗口
    int TcpConnect_Number = 0;            //客户端连接数量
    QTcpSocket *tcpSocket = nullptr;      //TCP通讯的Socket
};

#endif // MAINWIDGET_H
