#ifndef USER_H
#define USER_H

#include <QObject>

class USER : public QObject
{
    Q_OBJECT

public:
    explicit USER();
    ~USER();
    enum setUserFlagbit{
        Data,       //用户数据
        Number,     //用户账号
        Name,       //用户昵称
        Password,   //用户密码
        Sex,        //用户性别
        Headimg,    //用户头像
        Sign,       //用户个签
    };

public:
    //设置用户性别
    int set_UserSex(const QString &Sex);
    //设置用户昵称
    int set_UserName(const QString &Name);
    //设置用户签名
    int set_UserSign(const QString &Sign);
    //设置用户账号
    int set_UserNumber(const QString &Number);
    //获取用户信息
    const QString& get_UserInfo(setUserFlagbit flag);
    //设置用户头像
    int set_UserHeadimgPath(const QString &HeadimgPath);
    //设置全部对象
    int set_AllObject(const QString &user_Sex,const QString &user_Name,const QString &user_Sign,
                      const QString &user_Number,const QString &user_HeadimgPath);

signals:
    //更新信号
    void new_USER();

private:
    QString user_Sex;       //用户性别
    QString user_Name;      //用户昵称
    QString user_Sign;      //用户个签
    QString user_Type;      //用户类型
    QString user_Data;      //用户数据
    QString user_Number;    //用户账号
    QString user_Headimg;   //用户头像
};

extern USER my_USER;   //声明全局变量

#endif // USER_H
