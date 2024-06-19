#include "TcpThread.h"
#include <QDebug>

TcpThread::TcpThread(QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    //初始化对象
    read_type = "";
    read_data = "";
    read_number = "";

    //线程自动析构
    setAutoDelete(true);
}

TcpThread::TcpThread(const QString &number, QObject *parent)
    : QObject{parent}
    , user_Number{number}
    , QRunnable{}
{
    //初始化对象
    read_type = "";
    read_data = "";
    read_number = "";

    //线程自动析构
    setAutoDelete(true);
}

/*  设置传输的Json数据
 *  type：操作类型      data：数据      number：账号
 *  时间：2024/04/03   作者：Wild_Pointer
*/
QJsonObject TcpThread::set_PackageJSoninOperate(const QString &type, const QString &data, const QString &number)
{
    //初始化Json对象
    QJsonObject Object;
    Object["type"] = type;
    Object["data"] = data;
    Object["number"] = number;

    jsonObject = Object;
    return jsonObject;
}

/*  处理服务端返回的Json
 *  时间：2024/04/03   作者：Wild_Pointer
*/
void TcpThread::execute_JsonOperate(QByteArray jsondata)
{
    qDebug() << "处理服务端返回的Json";
    //解析数据
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsondata);
    QJsonObject jsonObject = jsonDocument.object();

    //从 JSON 对象中提取数据
    read_type = jsonObject["type"].toString();
    read_data = jsonObject["data"].toString();
    read_number = jsonObject["number"].toString();

    if(read_data == "True"){
        emit return_TestingMessage(true);
    }
    else{
        emit return_TestingMessage(false);
    }
}


TcpThread::~TcpThread()
{

}

void TcpThread::run()
{
    QJsonDocument jsonDocument(set_PackageJSoninOperate("Logo"," ",user_Number));
    QByteArray jsonData = jsonDocument.toJson();

    //提示主线程发送消息
    emit sending_inServer(jsonData);
}

