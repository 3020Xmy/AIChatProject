#include "AiThread.h"

AiThread::AiThread(QObject *parent)
    : QObject{parent}
    , QRunnable{}
{
    setAutoDelete(true);    //设置自动析构
}

AiThread::AiThread(const QString& response, QObject *parent)
    : QRunnable{}
    , QObject{parent}
{
    setAutoDelete(true);    //设置自动析构
    responseData = response;    //设置询问语句
}

AiThread::~AiThread()
{

}

/*  解析回复语句
 *  text：回复语句
 *  返回值：const QString&(解析后的语句)
*/
QString AiThread::handle_GetAnswerText(const QString &text)
{
    QString hex;
    //定义正则表达式，用于获取指定result值后的数据
    QRegularExpression regular("\"result\":\"(.*?)\"");
    QRegularExpressionMatch match = regular.match(text);
    QString matchedString = match.captured();   //捕获匹配正则表达式的数据

    //设置正则表达式，用于匹配\x后面的数据
    regular.setPattern("\\\\x([0-9A-Fa-f]{2})");

    //迭代正则表达式匹配的结果
    QRegularExpressionMatchIterator iteration = regular.globalMatch(matchedString);

    while (iteration.hasNext()) {       //循环遍历寻找匹配数据
        QRegularExpressionMatch match = iteration.next();
        hex = match.captured(1);
        bool ok;
        int decimal = hex.toInt(&ok, 16);
        if (ok) {
            matchedString.replace(match.capturedStart(), match.capturedLength(), QString(QChar(decimal)));
        }
    }

    //文本处理
    matchedString.replace("result\":\"", "");
    matchedString.replace("\\n", "\n");
    return matchedString;
}

/*  线程执行内容
*/
void AiThread::run()
{
    //解析回复语句
    emit getAnswer(handle_GetAnswerText(responseData));
}
