#ifndef SETUP_H
#define SETUP_H

#include <QMovie>
#include <QWidget>
#include "AiSetup.h"
#include <QMouseEvent>
#include "UserSetup.h"
#include "FileSetup.h"

namespace Ui {
class SetUp;
}

class SetUp : public QWidget
{
    Q_OBJECT

public:
    explicit SetUp(QWidget *parent = nullptr);
    ~SetUp();

////------------------------------------AI模块函数-------------------------------------------------------------
public:
    //初始化Ai设置界面
    int init_AiSetUp();
public slots:
    //请求设置Ai信息
    int request_SetAiInfo(const QString &type);
    //请求获取Ai信息
    int request_GetAiInfo(const QString &type);
signals:
    //转发至用户界面提醒设置Ai信息
    void relay_UserWidgetSetAiInfo(const QString &type);
    //转发至用户界面提醒获取Ai信息
    void relay_UserWidgetGetAiInfo(const QString &type);
private slots:
    //显示Ai设置界面
    void on_AiSetup_Btn_clicked();
////------------------------------------界面模块函数-------------------------------------------------------------
public:
    //初始化界面
    int initSetUp_Boundary();
private slots:
    //关闭界面函数
    void on_clos_Btn_clicked();
    //最小化界面函数
    void on_reduce_Btn_clicked();
    //用户设置界面函数
    void on_userSetup_Btn_clicked();
    //文件设置界面函数
    void on_fileSetup_Btn_clicked();
////------------------------------------事件模块函数-------------------------------------------------------------
protected:
    //鼠标移动事件
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    //鼠标点击事件
    virtual void mousePressEvent(QMouseEvent *event) override;
    //鼠标释放事件
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::SetUp *ui;
    bool move_Ok;         //是否移动
    QPoint move_point;    //移动的距离
    AiSetup *AiSetup_GUI;         //Ai设置界面
    UserSetup *UserSetup_GUI;     //用户设置界面
    FileSetup *FileSetup_GUI;     //文件设置界面
};

#endif // SETUP_H
