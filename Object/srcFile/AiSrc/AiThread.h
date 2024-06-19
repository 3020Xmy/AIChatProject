#ifndef AITHREAD_H
#define AITHREAD_H

#include <QObject>
#include <QThread>
#include <QRunnable>
#include <QRegularExpressionMatch>

class AiThread : public QObject, public QRunnable
{
    Q_OBJECT
public:
    ~AiThread();
    virtual void run() override;
    explicit AiThread(QObject *parent = nullptr);
    explicit AiThread(const QString& response, QObject *parent = nullptr);

public:
    //解析回复语句
    QString handle_GetAnswerText(const QString &text);

signals:
    //答复信号
    void getAnswer(const QString &response);

private:
    QString responseData;    //答复数据
};

#endif // AITHREAD_H
