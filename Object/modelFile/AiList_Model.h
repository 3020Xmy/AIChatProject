#ifndef AILIST_MODEL_H
#define AILIST_MODEL_H

#include <QWidget>
#include <QToolBox>
#include <QListWidget>
#include "uiFile/AiModel/AiInfo.h"

class AiList_Model : public QToolBox
{
    Q_OBJECT

public:
    ~AiList_Model();
    explicit AiList_Model(QWidget *parent = nullptr);

public:
    //新增机器人
    int handle_AddAiMessage();
    //新增机器人分组
    int handle_AddAiList(const QString &name);
    //将机器人插入分组
    int handle_MessageInsertlist(QSharedPointer<QListWidget> &List, QSharedPointer<AiInfo> &Message);

private:
    QVector<QSharedPointer<AiInfo>> MessageInfo_Vector;     //消息信息框容器
    QVector<QSharedPointer<QListWidget>> ListWidget_Vector; //分组信息框容器
};

#endif // AILIST_MODEL_H
