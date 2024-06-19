#ifndef AIINFO_H
#define AIINFO_H

#include <QWidget>
#include "srcFile/AiSrc/AI.h"
#include "uiFile/AiModel/AiChat.h"

namespace Ui {
class AiInfo;
}

class AiInfo : public QWidget
{
    Q_OBJECT

public:
    ~AiInfo();
    explicit AiInfo(QWidget *parent = nullptr);

public:
    //初始化窗口
    int init_AiInfoWidget();
public slots:
    //设置窗口消息
    int set_AiInfoWidgetInfo();
protected:
    //双击机器人显示对话框
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::AiInfo *ui;
    QSharedPointer<AiChat> Chat;        //AI聊天界面
};

#endif // AIINFO_H
