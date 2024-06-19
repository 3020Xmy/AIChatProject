#include "AI.h"
#include <QDebug>

AI::AI()
{
    //初始化对象
    ai_Name = "智能机器人";
    ai_Sign = "你好！我是小源，你的专属聊天机器人";
    ai_ApiKey = "";
    ai_ApiSecret = "";
}

AI::~AI()
{

}

/*  设置机器人昵称
 *  name：设置的昵称
*/
int AI::handle_SetAiName(const QString &name)
{
    ai_Name = name;
    return 1;
}

/*  设置机器人介绍
 *  sign：设置的介绍
*/
int AI::handle_SetAiSign(const QString &sign)
{
    ai_Sign = sign;
    return 1;
}

/*  鉴权元素APIKey
 *  ApiKey：设置的APIKey
*/
int AI::handle_SetApiKey(const QString &ApiKey)
{
    ai_ApiKey = ApiKey;
    return 1;
}

/*  设置鉴权元素APISecret
 *  ApiSecret：设置的APISecret
*/
int AI::handle_SetApiSecret(const QString &ApiSecret)
{
    ai_ApiSecret = ApiSecret;
    return 1;
}

/*  设置全部对象
 *  ai_Name：机器人名称     ai_Sign：机器人介绍
 *  ai_ApiKey：鉴权元素APIKey    ai_ApiSecret：鉴权元素APISecret
*/
int AI::handle_SetAllObject(const QString &ai_Name, const QString &ai_Sign,
                                   const QString &ai_ApiKey, const QString &ai_ApiSecret)
{
    handle_SetAiName(ai_Name);
    handle_SetAiSign(ai_Sign);
    handle_SetApiKey(ai_ApiKey);
    handle_SetApiSecret(ai_ApiSecret);

    emit new_AIInfo();
    return 1;
}

/*  获取机器人信息
 *  Type：信息类型
 *  返回值：const QString&(具体机器人信息)
*/
const QString& AI::handle_GetAiInfo(setAiFlagbit flag)
{
    //判断枚举值
    switch (flag){
    case aiName:
        return ai_Name;     //返回用户数据
        break;
    case aiSign:
        return ai_Sign;     //返回用户账号
        break;
    case aiAPIKey:
        return ai_ApiKey;   //返回用户昵称
        break;
    case aiAPISecret:
        return ai_ApiSecret;//返回用户性别
        break;
    }
}
