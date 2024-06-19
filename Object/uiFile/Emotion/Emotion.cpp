#include "Emotion.h"
#include "ui_Emotion.h"

Emotion::Emotion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Emotion)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint|Qt::FramelessWindowHint);
    ui->label_1->installEventFilter(this);
    ui->label_2->installEventFilter(this);
    ui->label_3->installEventFilter(this);
    ui->label_4->installEventFilter(this);
    ui->label_5->installEventFilter(this);
    ui->label_6->installEventFilter(this);
    ui->label_7->installEventFilter(this);
    ui->label_8->installEventFilter(this);
    ui->label_9->installEventFilter(this);
    ui->label_10->installEventFilter(this);
    ui->label_11->installEventFilter(this);
    ui->label_12->installEventFilter(this);
    ui->label_13->installEventFilter(this);
    ui->label_14->installEventFilter(this);
    ui->label_15->installEventFilter(this);
    ui->label_16->installEventFilter(this);
    ui->label_17->installEventFilter(this);
    ui->label_18->installEventFilter(this);
    ui->label_19->installEventFilter(this);
    ui->label_20->installEventFilter(this);
    ui->label_21->installEventFilter(this);
    ui->label_22->installEventFilter(this);
    ui->label_23->installEventFilter(this);
    ui->label_24->installEventFilter(this);
    ui->label_25->installEventFilter(this);
    ui->label_26->installEventFilter(this);
    ui->label_27->installEventFilter(this);
    ui->label_28->installEventFilter(this);
    ui->label_29->installEventFilter(this);
    ui->label_30->installEventFilter(this);
}

Emotion::~Emotion()
{
    delete ui;
}

/*  事件过滤器
 *  object：对象   event：事件
*/
bool Emotion::eventFilter(QObject *object, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonPress && object==ui->label_1)
    {
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_1.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_2){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_2.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_3){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_3.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_4){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_4.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_5){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_5.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_6){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_6.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_7){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_7.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_8){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_8.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_9){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_9.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_10){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_10.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_11){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_11.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_12){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_12.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_13){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_13.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_14){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_14.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_15){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_15.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_16){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_16.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_17){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_17.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_18){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_18.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_19){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_19.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_20){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_20.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_21){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_21.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_22){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_22.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_23){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_23.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_24){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_24.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_25){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_25.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_26){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_26.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_27){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_27.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_28){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_28.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_29){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_29.png"));
        hide();
    }
    else if(event->type()==QEvent::MouseButtonPress && object==ui->label_30){
        emit imgurl(QString(":/new/Emotion/icons/Emotion/lab_30.png"));
        hide();
    }
    return false;
}
