#ifndef AI_H
#define AI_H

#include <QObject>

class AI : public QObject
{
    Q_OBJECT

public:
    ~AI();
    explicit AI();
    enum setAiFlagbit{
        aiName,       //AI昵称
        aiSign,       //AI介绍
        aiAPIKey,     //AIKey
        aiAPISecret   //AISecret
    };

public:
    //设置机器人昵称
    int handle_SetAiName(const QString &name);
    //设置机器人介绍
    int handle_SetAiSign(const QString &sign);
    //设置鉴权元素APIKey
    int handle_SetApiKey(const QString &ApiKey);
    //设置鉴权元素APISecret
    int handle_SetApiSecret(const QString &ApiSecret);
    //获取机器人信息
    const QString& handle_GetAiInfo(setAiFlagbit flag);
    //设置全部对象
    int handle_SetAllObject(const QString &ai_Name, const QString &ai_Sign, const QString &ai_ApiKey,
                            const QString &ai_ApiSecret);

signals:
    //更新信号
    void new_AIInfo();

private:
    QString ai_Name;           //机器人名称
    QString ai_Sign;           //机器人介绍
    QString ai_ApiKey;         //鉴权元素APIKey
    QString ai_ApiSecret;      //鉴权元素APISecret
};

extern AI my_AI;   //声明全局变量

#endif // AI_H
