#ifndef EMOTION_H
#define EMOTION_H

#include <QLabel>
#include <QWidget>
#include <QGridLayout>

namespace Ui {
class Emotion;
}

class Emotion : public QWidget
{
    Q_OBJECT

public:
    ~Emotion();
    explicit Emotion(QWidget *parent = 0);
    //事件过滤器
    bool eventFilter(QObject *object, QEvent *e);

signals:
     //传输表情地址信号
     void imgurl(QString imgurl);

private:
    Ui::Emotion *ui;

};

#endif // EMOTION_H
