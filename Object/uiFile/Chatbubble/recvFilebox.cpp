#include "recvFilebox.h"
#include "ui_recvFilebox.h"

recvFilebox::recvFilebox(QWidget *parent) :
    ChatBox(parent),
    ui(new Ui::recvFilebox)
{
    ui->setupUi(this);

    fileSize = 0;
    filePath = " ";
    filestate = false;
    ui->progressBar->setMinimum(0);
}

recvFilebox::~recvFilebox()
{
    delete ui;
}

/*  更新接收进度条下载信息
 *  recvsize：接收进度
*/
int recvFilebox::set_ReceiveRecvsize(int recvsize)
{
    if(recvsize == fileSize){
        filestate = true;
    }
    ui->progressBar->setValue(recvsize);
    return 1;
}

/*  处理头像
 *  imgpath：头像路径
*/
int recvFilebox::handle_HeadImg(const QString &imgpath)
{
    QPixmap pixmap(imgpath);
    pixmap = pixmap.scaled(ui->headImg_lab->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap roundPixmap(ui->headImg_lab->size());
    roundPixmap.fill(Qt::transparent);
    QPainter painter(&roundPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(roundPixmap.rect());
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, pixmap);
    ui->headImg_lab->setPixmap(roundPixmap);
    return 1;
}

/*  设置文件信息
 *  name：文件名称    size：文件大小
 */
int recvFilebox::set_FileInfo(const QString &name, const qint64 &size)
{
    ui->filename_lab->setText(name);
    double number = size;
    QString Str = "B";  //设置大小单位
    fileSize = size;
    ui->progressBar->setMaximum(fileSize);
    if(size > 2048){    //设置显示的文件大小
        Str = "MB";
        number = static_cast<double>(size)/1024/1024;
    }
    filePath = QStringLiteral("%1/File/%3").arg(QDir::currentPath()).arg(name);
    QString str = QStringLiteral("%1%2").arg(QString::number(number,'f',2)).arg(Str);
    ui->filesize_lab->setText(str);
    ui->progressBar->setMinimum(number);
    return 1;
}

/*  双击事件
 *  event：事件
*/
void recvFilebox::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(filestate){
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    }else{
        emit handle_RequestServerSendingFile();
    }
}
