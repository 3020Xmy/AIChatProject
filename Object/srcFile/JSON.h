#ifndef JSON_H
#define JSON_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

class JSON : public QObject
{
    Q_OBJECT
public:
    ~JSON();
    explicit JSON();

public:
    //将操作封装json
    const QJsonObject& Package_OperationsIntoJSON(const QString &type,const QString &operate);

private:
    QJsonObject jsonObject;     //json对象
};

extern JSON my_JSON;   //声明全局变量

#endif // JSON_H
