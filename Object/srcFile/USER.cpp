#include "USER.h"

USER::USER()
{
    //初始化对象
    user_Name = "";
    user_Number= "";
    user_Sex = "男";
    user_Sign = "当前还没有个性签名喔！";
    user_Headimg = ":/new/Chat/icons/Chat/logo_Show.png";
}

USER::~USER()
{

}

/*  设置用户性别
 *  Sex：性别
*/
int USER::set_UserSex(const QString &Sex)
{
    user_Sex = Sex;
    return 1;
}

/*  设置用户昵称
 *  Name：昵称
*/
int USER::set_UserName(const QString &Name)
{
    user_Name = Name;
    return 1;
}

/*  设置用户签名
 *  Sign：签名
*/
int USER::set_UserSign(const QString &Sign)
{
    user_Sign = Sign;
    return 1;
}

/*  设置用户账号
 *  Number：账号
*/
int USER::set_UserNumber(const QString &Number)
{
    user_Number = Number;
    return 1;
}

/*  设置用户头像
 *  HeadimgPath：头像路径
*/
int USER::set_UserHeadimgPath(const QString &HeadimgPath)
{
    user_Headimg = HeadimgPath;
    return 1;
}

/*  获取用户信息
 *  Type：信息类型
 *  返回值：const QString&(用户信息)
*/
const QString& USER::get_UserInfo(setUserFlagbit flag)
{
    //判断枚举值
    switch (flag){
    case Data:
        return user_Data;       //返回用户数据
        break;
    case Number:
        return user_Number;     //返回用户账号
        break;
    case Name:
        return user_Name;       //返回用户昵称
        break;
    case Sex:
        return user_Sex;        //返回用户性别
        break;
    case Headimg:
        return user_Headimg;    //返回用户头像
        break;
    case Sign:
        return user_Sign;       //返回用户个签
        break;
    }
}

/*  设置全部对象
 *  user_Sex：用户性别   user_Name：用户昵称   user_Sign：用户签名    user_Number：用户账号    user_Headimg：用户头像
*/
int USER::set_AllObject(const QString &user_Sex,const QString &user_Name,const QString &user_Sign,
                         const QString &user_Number,const QString &user_Headimg)
{
    //设置信息
    set_UserSex(user_Sex);
    set_UserName(user_Name);
    set_UserSign(user_Sign);
    set_UserNumber(user_Number);
    set_UserHeadimgPath(user_Headimg);
    //发出更新信号
    emit new_USER();
    return 1;
}


