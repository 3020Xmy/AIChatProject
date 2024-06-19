#include "Sendbox.h"
#include "ui_Sendbox.h"

Sendbox::Sendbox(QWidget *parent) :
    ChatBox(parent),
    ui(new Ui::Sendbox)
{
    ui->setupUi(this);
}

Sendbox::~Sendbox()
{
    delete ui;
}

////------------------------------------界面模块函数-----------------------------------------------------------
/*  返回气泡高度
 *  返回值int：气泡高度
*/
int Sendbox::return_SendBoxHeight()
{
    return height;
}

/*  处理大小变化事件
 *  event：事件
*/
void Sendbox::resizeEvent(QResizeEvent *event)
{
    handle_SendBoxMarginsSize();
}

/*  处理气泡大小
*/
int Sendbox::handle_SendBoxMarginsSize()
{
    ui->user_Recvmsg->document()->adjustSize();
    QMargins margins = ui->user_Recvmsg->contentsMargins(); //获取边框的距离
    ui->user_Recvmsg->setFixedWidth(ui->user_Recvmsg->document()->size().width()+margins.left()+margins.right());
    ui->user_Recvmsg->setFixedHeight(ui->user_Recvmsg->document()->size().height()+margins.top()+margins.bottom());
    return 1;
}

/*  处理头像
 *  imgpath：头像路径
*/
int Sendbox::handle_HeadImg(const QString &imgpath)
{
    QPixmap pixmap(imgpath);
    pixmap = pixmap.scaled(ui->img_lab->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap roundPixmap(ui->img_lab->size());
    handle_SetHeadImgAttribute(&pixmap,&roundPixmap);
    ui->img_lab->setPixmap(roundPixmap);
    return 1;
}

////------------------------------------发送图片模块函数-----------------------------------------------------------
/*  处理发送的图片
 *  img：图片路径
*/
int Sendbox::handle_SendBoxShowImg(const QString &imgpath)
{
    QImage image = QImageReader(imgpath).read();
    if (image.width() > 280 || image.height() > 250) {  //调整图片大小
        image = image.scaled(280, 250, Qt::KeepAspectRatio);
    }
    QSize newSize = QSize(image.width(), image.height());  //设置图片大小
    if(handle_GetSendBoxDocumentInsterImg(image,imgpath,newSize)){
        return 1;
    }
    return 0;
}

/*  处理发送的表情
 *  emotion：表情路径
*/
int Sendbox::handle_SendBoxShowEmotion(const QString &emotion)
{
    QSize newSize = QSize(30, 30);  //设置表情大小
    QImage image = QImageReader(emotion).read();
    image = image.scaled(newSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);    //设置表情缩放算法
    if(handle_GetSendBoxDocumentInsterImg(image,emotion,newSize)){
        return 1;
    }
    return 0;
}

/*  获取气泡文档并插入图片
 *  image：图片    path：图片路径    size：图片大小
*/
int Sendbox::handle_GetSendBoxDocumentInsterImg(const QImage& image, const QString &path, const QSize& size)
{
    text_Doc = ui->user_Recvmsg->document();
    text_Doc->addResource(QTextDocument::ImageResource, QUrl(path), QVariant(image));
    QTextCursor cursor = ui->user_Recvmsg->textCursor();
    QTextImageFormat imgFormat;
    imgFormat.setWidth(size.width());
    imgFormat.setHeight(size.height());
    imgFormat.setName(path);
    cursor.insertImage(imgFormat);
    return 1;
}

////------------------------------------发送图片模块函数-----------------------------------------------------------
/*  设置发送的文字
 *  text：文字
*/
int Sendbox::handle_SendBoxShowText(QString text)
{
    ui->user_Recvmsg->setText(text);
    height = ui->user_Recvmsg->height();
    resize(50,return_SendBoxHeight()); // 调整 QWidget 的大小
    ui->widget->resize(50,return_SendBoxHeight());
    return 1;
}



