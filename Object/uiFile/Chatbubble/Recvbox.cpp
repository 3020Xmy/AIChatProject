#include "Recvbox.h"
#include "ui_Recvbox.h"

Recvbox::Recvbox(QWidget *parent) :
    ChatBox(parent),
    ui(new Ui::Recvbox)
{
    ui->setupUi(this);
    //设置气泡大小
    connect(ui->friend_Recvmsg,&QTextEdit::textChanged,this,&Recvbox::handle_RecvBoxSize);
}

Recvbox::~Recvbox()
{
    delete ui;
}

/*  设置发送的文字
 *  text：文字
*/
int Recvbox::handle_RecvBoxShowText(QString text)
{
    ui->friend_Recvmsg->setText(text);
    height = ui->friend_Recvmsg->height();
    resize(50, return_RecvBoxHeight()); // 调整 QWidget 的大小
    ui->widget->resize(50,return_RecvBoxHeight());
    return 1;
}

/*  处理接收的图片
 *  img:图片路径
*/
int Recvbox::handle_RecvBoxShowImg(const QString &img)
{
    QImage image = QImageReader(img).read();
    if (image.width() > 280 || image.height() > 250) {  //调整图片大小
        image = image.scaled(280, 250, Qt::KeepAspectRatio);
    }
    QSize newSize = QSize(image.width(), image.height());  //设置图片大小
    if(handle_GetRecvBoxDocumentInsterImg(image,img,newSize)){
        return 1;
    }
    return 0;
}

/*  处理气泡大小
*/
int Recvbox::handle_RecvBoxSize()
{
    QTextDocument* doc = ui->friend_Recvmsg->document();
    QTextEdit* textEdit = ui->friend_Recvmsg;

    //textEdit内的document和边框的距离
    QMargins margins = textEdit->contentsMargins();
    doc->adjustSize();
    textEdit->setFixedWidth(doc->size().width()+margins.left()+margins.right());
    textEdit->setFixedHeight(doc->size().height()+margins.top()+margins.bottom());
    return 1;
}

/*  返回气泡高度
*/
int Recvbox::return_RecvBoxHeight()
{
    return height;
}

/*  处理大小变化事件
 *  event：事件
*/
void Recvbox::resizeEvent(QResizeEvent *event)
{
    handle_RecvBoxSize();
}

/*  处理头像
 *  imgpath：头像路径
*/
int Recvbox::handle_HeadImg(const QString &imgpath)
{
    QPixmap pixmap(imgpath);
    pixmap = pixmap.scaled(ui->label->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap roundPixmap(ui->label->size());
    handle_SetHeadImgAttribute(&pixmap,&roundPixmap);
    ui->label->setPixmap(roundPixmap);
    return 1;
}

/*  处理发送的表情
 *  emotion：表情路径
*/
int Recvbox::handle_RecvBoxShowEmotion(const QString &emotion)
{
    QSize newSize = QSize(30, 30);  //设置表情大小
    QImage image = QImageReader(emotion).read();
    image = image.scaled(newSize,Qt::KeepAspectRatio, Qt::SmoothTransformation);    //设置表情缩放算法
    if(handle_GetRecvBoxDocumentInsterImg(image,emotion,newSize)){
        return 1;
    }
    return 0;
}

/*  获取气泡文档并插入图片
 *  image：图片    path：图片路径    size：图片大小
*/
int Recvbox::handle_GetRecvBoxDocumentInsterImg(const QImage& image, const QString& path, const QSize& size)
{
    text_Doc = ui->friend_Recvmsg->document();
    text_Doc->addResource(QTextDocument::ImageResource, QUrl(path), QVariant(image));
    QTextCursor cursor = ui->friend_Recvmsg->textCursor();
    QTextImageFormat imgFormat;
    imgFormat.setWidth(size.width());
    imgFormat.setHeight(size.height());
    imgFormat.setName(path);
    cursor.insertImage(imgFormat);
    return 1;
}
