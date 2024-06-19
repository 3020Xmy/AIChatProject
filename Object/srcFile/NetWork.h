#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QUrlQuery>
#include "AiSrc/AI.h"
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QRegularExpression>
#include <QNetworkAccessManager>

class NetWork : public QObject
{
    Q_OBJECT
public:
    ~NetWork();
    explicit NetWork();

public:
    //获取Accesstoken
    int handle_GetAccessToken();
    //更新鉴权元素
    int handle_NewKeyandSecret();
    //判断是否存在鉴权元素
    bool handle_InspectKeyandSecret();
    //修改询问语句
    QString handle_SetEnquireText(const QString &enquiretext);
    //设置鉴权元素
    int handle_SetAuthentication(const QString &key, const QString &secret);

private:
    QString APIKey;                  //鉴权元素APIKey
    QString APISecret;               //鉴权元素APISecret
    QByteArray payload;              //请求内容
    QString accessToken;             //返回的AccessToken
    QNetworkReply *reply;            //发送POST请求
    QNetworkRequest request;         //创建POST请求
    QRegularExpression Regex;        //正则表达式对象
    QNetworkAccessManager *manager;  //网络访问管理器
};

extern NetWork my_NETWORK;   //声明全局变量

#endif // NETWORK_H
