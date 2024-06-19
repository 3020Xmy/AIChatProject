#include "connect.h"

connect::connect()
{
    //设置本机端口
    Local_connectPort = 3020;
    //获取本机名
    Local_connectName = QconnectInfo::localconnectName();
    //获取本机信息
    Local_connectInfo = QconnectInfo::fromName(Local_connectName);

    get_HoatIPv4();
}

connect::~connect()
{

}

/*  获取本机IPv4地址
 *  时间：2024/03/24   作者：Wild_Pointer
*/
void connect::get_HoatIPv4()
{
    //获取IP列表
    QList<QconnectAddress> listAddress = Local_connectInfo.addresses();
    if(!listAddress.isEmpty()){
        //获取IPV4地址
        foreach (QconnectAddress connect, listAddress) {
            if(QAbstractSocket::IPv4Protocol == connect.protocol()){
                Local_HoatIPv4 = connect.toString();
                break;
            }
        }
    }
}
