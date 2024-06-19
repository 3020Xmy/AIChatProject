#ifndef AISETUP_H
#define AISETUP_H

#include <QWidget>
#include <QMessageBox>
#include "srcFile/AiSrc/AI.h"
#include <QRegularExpressionValidator>

namespace Ui {
class AiSetup;
}

class AiSetup : public QWidget
{
    Q_OBJECT

public:
    explicit AiSetup(QWidget *parent = nullptr);
    ~AiSetup();

public:
    //请求获取Ai信息
    int get_InitAiInfo();
    //设置控件信息
    int set_AiWidgetInfo();
private slots:
    //确定修改信息
    int on_determine_Btn_clicked();
signals:
    //请求设置Ai信息
    void set_AiInfo(const QString &type);
    //请求获取Ai信息
    void get_AiInfo(const QString &type);

private:
    Ui::AiSetup *ui;
    QRegularExpressionValidator *aiName_Validator;      //Ai名称输入验证器
    QRegularExpressionValidator *aiSign_Validator;      //Ai介绍输入验证器
};

#endif // AISETUP_H
