#include "sendFilebox.h"
#include "ui_sendFilebox.h"

sendFilebox::sendFilebox(QWidget *parent) :
    ChatBox(parent),
    ui(new Ui::sendFilebox)
{
    ui->setupUi(this);

    fileSize = 0;
    ui->progressBar->setMinimum(0);
}

sendFilebox::~sendFilebox()
{
    delete ui;
}

/*  更新进度条下载信息
 *  recvsize：下载进度
*/
int sendFilebox::set_Recvsize(int recvsize)
{
    ui->progressBar->setValue(recvsize);
    return 1;
}

/*  设置文件路径
 *  path：文件路径
*/
int sendFilebox::set_FilePath(const QString& path)
{
    filePath = path;
    return 1;
}

/*  设置文件信息
 *  name：文件名称   size：文件大小
*/
int sendFilebox::set_FileInfo(const QString &name, const qint64 &size)
{
    ui->filename_lab->setText(name);
    double number = size;
    QString Str = "B";
    fileSize = size;
    ui->progressBar->setMaximum(fileSize);
    if(size > (1024*1024)){     //设置显示的文件大小
        Str = "MB";
        number = static_cast<double>(size)/1024/1024;
    }
    QString str = QStringLiteral("%1%2").arg(QString::number(number,'f',2)).arg(Str);
    ui->filesize_lab->setText(str);
    ui->progressBar->setMinimum(number);
    return 1;
}

/*  设置头像
 *  imgpath：头像路径
*/
int sendFilebox::handle_HeadImg(const QString &imgpath)
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

/*  鼠标双击事件
 *  event：事件
*/
void sendFilebox::mouseDoubleClickEvent(QMouseEvent *event)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));   //使用QDesktopServices 来打开文件的默认程序
}
