#include "FriendChat.h"
#include "ui_FriendChat.h"

FriendChat::FriendChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendChat)
{
    ui->setupUi(this);
}

FriendChat::FriendChat(const QString &name, const QString &sign,
                       const QString &number, const QString headimg,
                       const QString &state, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendChat)
{
    ui->setupUi(this);

    type = " ";
    friend_name = name;
    friend_sign = sign;
    friend_state = state;
    friend_number = number;
    friend_headimg = headimg;
    init_FriendChatWidget();    //初始化界面
}

FriendChat::~FriendChat()
{
    delete emotion;
    delete send_File;
    delete ui;
}

////---------------------------------------事件模块函数-------------------------------------------------------
/*  事件过滤器
 *  watched：对象    event：事件
*/
bool FriendChat::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress && watched==ui->Emotion_lab){
        int x = this->pos().x();
        int y = this->pos().y() + 325;
        emotion->move(x,y);
        emotion->show();
    }
}

/*  鼠标点击事件
 *  event：事件
*/
void FriendChat::mousePressEvent(QMouseEvent *event)
{
    emotion->hide();
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

/*  鼠标释放事件
 *  event：事件
*/
void FriendChat::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  鼠标移动事件
 *  event：事件
*/
void FriendChat::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

////---------------------------------------界面模块函数------------------------------------------------------
/*  初始化好友聊天界面
*/
int FriendChat::init_FriendChatWidget()
{
    //初始化对象
    emotion = new Emotion();

    //初始化属性
    ui->FriendHead->setScaledContents(true);    //设置头像大小自适应
    setWindowFlags(Qt::WindowType::FramelessWindowHint);    //设置界面透明与去掉边框
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);   //设置listWidget关闭选中
    ui->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); //设置listWidget为以像素大小进行移动

    //初始化控件对象
    ui->FriendName->setText(friend_name);
    ui->FriendSign->setText(friend_sign);
    ui->FriendNumber->setText(friend_number);
    QPixmap originalPixmap(friend_headimg);
    originalPixmap = originalPixmap.scaled(ui->FriendHead->width(),
                                           ui->FriendHead->height(), Qt::KeepAspectRatio);
    ui->FriendHead->setPixmap(originalPixmap);

    //初始化样式表
    QFile file(":/new/qss/qssFile/scrollbar.qss");
    file.open(QFile::ReadOnly);
    ui->listWidget->verticalScrollBar()->setStyleSheet(file.readAll()); //设置listWidet对象样式
    if(friend_state == "1"){        //设置头像状态样式
        ui->FriendHead->setStyleSheet("border: 2px solid green;");
    }
    else{
        ui->FriendHead->setStyleSheet("border: 2px solid black;");
    }

    ui->Emotion_lab->installEventFilter(this);  //初始化事件过滤器
    //发送表情
    connect(emotion,&Emotion::imgurl,this,&FriendChat::handle_UserSendingEmotion);
    return 1;
}

/*  处理输入框显示图片
 *  path：图片路径
*/
int FriendChat::handle_TextEditShowImg(const QString &path)
{
    QTextCursor curosr = ui->text_Edit->textCursor();
    QTextImageFormat imgFormat;
    imgFormat.setWidth(200);
    imgFormat.setHeight(300);
    imgFormat.setName(path);
    curosr.insertImage(imgFormat);  //插入图片
    return 1;
}

/*  修改好友信息
 *  headPath：头像路径   name：好友昵称   sign：好友个性签名
*/
int FriendChat::set_FriendInfo(const QString &headPath,const QString &name,const QString &sign)
{
    QPixmap Img(headPath);
    Img = Img.scaled(ui->FriendHead->width(),
                     ui->FriendHead->height(), Qt::KeepAspectRatio);
    ui->FriendHead->setPixmap(Img); //设置头像
    ui->FriendName->setText(name);  //设置昵称
    ui->FriendSign->setText(sign);  //设置好友个性签名
    return 1;
}

/*  获取好友账号
 *  返回值：QString(好友账号)
*/
QString FriendChat::get_FriendNumber()
{
    return friend_number;
}

/*  发送按钮
*/
void FriendChat::on_sending_Btn_clicked()
{
    if(type == "sendingImg"){
        handle_UserSendingImg();        //处理用户发送的图片
    }
    else if(type == "sendingFile"){
        handle_UserSendingFile();       //处理用户发送的文件
    }else{
        handle_UserSendingMessage();   //处理用户发送的信息
    }
    type = " ";
}

/*  最小化界面函数
*/
void FriendChat::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  Top关闭界面函数
*/
void FriendChat::on_close_Btntop_clicked()
{
    this->close();
}

/*  Bottom关闭界面函数
*/
void FriendChat::on_close_Btnbottom_clicked()
{
    this->close();
}

/*  处理项更新
 *  item：项    box：替换的项
*/
int FriendChat::handle_NewItem(QListWidgetItem *item, ChatBox* box)
{
    ui->listWidget->setItemWidget(item,box);
    ui->text_Edit->clear(); //清空文本输入框
    ui->listWidget->setCurrentRow(ui->listWidget->model()->rowCount() - 1); //每次更新消息都显示最新的项
    return 1;
}

////---------------------------------------消息发送模块函数------------------------------------------------------
/*  处理接收的好友消息
 *  message：消息
*/
int FriendChat::handle_FriendMessage(const QString &message)
{
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);    //初始化气泡并输出
    Recvbox *recv_item = new Recvbox(this);
    recv_item->handle_RecvBoxShowText(message);
    recv_item->handle_HeadImg(friend_headimg); //设置头像
    item->setSizeHint(QSize(250,recv_item->return_RecvBoxHeight()+50));
    handle_NewItem(item,recv_item);
    return 1;
}

/*  处理用户发送的信息
*/
int FriendChat::handle_UserSendingMessage()
{
    Sendbox *send_item=new Sendbox(this);
    QListWidgetItem *item=new QListWidgetItem(ui->listWidget);  //初始化气泡
    send_item->handle_SendBoxShowText(ui->text_Edit->toPlainText());
    item->setSizeHint(QSize(200,send_item->return_SendBoxHeight()+50));
    send_item->handle_HeadImg(my_USER.get_UserInfo(USER::Headimg)); //设置头像
    emit handle_SendingMessage(friend_number,ui->text_Edit->toPlainText());   //请求发送消息
    handle_NewItem(item,send_item);
    return 1;
}

////---------------------------------------表情发送模块函数------------------------------------------------------
/*  处理用户发送的表情
 *  imgpath：图片路径
*/
int FriendChat::handle_UserSendingEmotion(const QString &imgpath)
{
    QListWidgetItem *item=new QListWidgetItem(ui->listWidget);
    Sendbox * send_item = new Sendbox(this);
    item->setSizeHint(QSize(200,90));
    send_item->handle_HeadImg(my_USER.get_UserInfo(USER::Headimg)); //设置头像
    send_item->handle_SendBoxShowEmotion(imgpath);
    handle_NewItem(item,send_item);
    emit handle_SendingEmotion(friend_number,imgpath);
    return 1;
}

/*  处理接收的好友表情
 *  emotion：表情
*/
int FriendChat::handle_FriendEmotion(const QString &emotion)
{
    //初始化气泡并输出
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    Recvbox *recv_item = new Recvbox(this);
    item->setSizeHint(QSize(200,90));
    recv_item->handle_HeadImg(friend_headimg); //设置头像
    recv_item->handle_RecvBoxShowEmotion(emotion);
    handle_NewItem(item,recv_item);
    return 1;
}

////---------------------------------------图片发送模块函数------------------------------------------------------
/*  显示好友发送的图片
 *  img：图片路径
*/
int FriendChat::handle_FriendImg(const QString &img)
{
    //初始化气泡并输出
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    Recvbox *recv_item = new Recvbox(this);
    item->setSizeHint(QSize(310,310));
    recv_item->handle_HeadImg(friend_headimg); //设置头像
    recv_item->handle_RecvBoxShowImg(img);
    handle_NewItem(item,recv_item);
    return 1;
}

/*  将发送的图片信息打包为Json格式
 *  imgpath：图片路径
 *  返回值：QJsonObject(打包好的Json对象)
*/
QJsonObject FriendChat::handle_ImgPackageAsJSON(const QString &imgpath)
{
    QJsonObject Json;
    Json.insert("type","friend_SendingImg");
    QJsonObject dataObj;
    dataObj.insert("sendingObj",my_USER.get_UserInfo(USER::Number));
    dataObj.insert("receiveObj",friend_number);
    Json.insert("data",dataObj);
    Json.insert("fileInfo",handle_FileInfoPackageAsJSON(imgpath));
    return Json;
}

/*  处理用户发送的图片
*/
int FriendChat::handle_UserSendingImg()
{
    QListWidgetItem *item=new QListWidgetItem(ui->listWidget);
    Sendbox *send_item=new Sendbox(this);
    item->setSizeHint(QSize(310,310));
    send_item->handle_HeadImg(my_USER.get_UserInfo(USER::Headimg)); //设置头像
    send_item->handle_SendBoxShowImg(filePath);
    handle_NewItem(item,send_item);
    emit handle_SendingFilePath(filePath); //将发送的文件告知Tcp
    return 1;
}

/*  选择图片函数
*/
void FriendChat::on_img_Btn_clicked()
{
    filePath = QFileDialog::getOpenFileName(this,"选择图片",".","(*.png *.jpeg *.jpg *.bmp *.gif *.tiff)");
    if(filePath.isEmpty()){
        return;
    }
    type = "sendingImg";    //设置操作类型
    QImage image = QImageReader(filePath).read();
    if (image.width() > 200 || image.height() > 300) {  //调整图片大小
        image = image.scaled(200, 300, Qt::KeepAspectRatio);
    }
    QTextDocument* text_Doc = ui->text_Edit->document();    //获取文本文档，并向文档添加图片资源
    text_Doc->addResource(QTextDocument::ImageResource,filePath,QVariant(image));
    QTextCursor curosr = ui->text_Edit->textCursor();
    handle_TextEditShowImg(filePath);   //在输入框中插入图片
    emit handle_SendingImgInfoJson(handle_ImgPackageAsJSON(filePath));
}

////---------------------------------------文件发送模块函数------------------------------------------------------
/*  处理用户发送的文件
*/
int FriendChat::handle_UserSendingFile()
{
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    item->setSizeHint(QSize(110,110));
    send_File = new sendFilebox(this);
    QFile file(filePath);
    QFileInfo fileInfo(file);   //使用 QFileInfo 获取文件信息
    send_File->set_FilePath(filePath);
    send_File->set_FileInfo(fileInfo.fileName(),fileInfo.size());
    send_File->handle_HeadImg(my_USER.get_UserInfo(USER::Headimg));
    handle_NewItem(item, send_File);
    emit handle_SendingFilePath(filePath); //将发送的文件告知Tcp
    return 1;
}

/*  转发发送文件请求至FriendInfo
*/
int FriendChat::handle_ForwardSendingFileRequest()
{
    emit handle_ForwardFileRequest();
    return 1;
}

/*  处理用户发送的文件进度
 *  size：发送进度
*/
int FriendChat::handle_SendingFileSchedule(qint64 size)
{
    send_File->set_Recvsize(size);
    return 1;
}

/*  处理接收的文件进度
 *  size：接收进度
*/
int FriendChat::handle_ReceiveFileSchedule(qint64 size)
{
    recv_File->set_ReceiveRecvsize(size);
    return 1;
}

/*  显示好友发送的文件气泡
 *  jsonObject：文件信息
*/
int FriendChat::handle_ShowFileBox(const QJsonObject &jsonObject)
{
    QJsonObject Object = jsonObject["data"].toObject();
    QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
    item->setSizeHint(QSize(110,110));
    recv_File = new recvFilebox(this);
    connect(recv_File,&recvFilebox::handle_RequestServerSendingFile,this,&FriendChat::handle_ForwardSendingFileRequest);
    recv_File->handle_HeadImg(friend_headimg);
    recv_File->set_FileInfo(Object["fileName"].toString(),Object["fileSize"].toInt());
    handle_NewItem(item, recv_File);
    return 1;
}

/*  将发送的文件信息打包为Json格式
 *  Path：文件路径
 *  返回值：QJsonObject(打包好的Json对象)
 */
QJsonObject FriendChat::handle_FilePackageAsJSON(const QString &Path)
{
    QJsonObject Json;
    Json.insert("type","friend_SendingFile");
    QJsonObject dataObj;
    dataObj.insert("sendingObj",my_USER.get_UserInfo(USER::Number));
    dataObj.insert("receiveObj",friend_number);
    Json.insert("data",dataObj);
    Json.insert("fileInfo",handle_FileInfoPackageAsJSON(Path));
    return Json;
}

/*  选择传输文件函数
*/
void FriendChat::on_file_Btn_clicked()
{
    filePath = QFileDialog::getOpenFileName(this,"选择文件",".","*.*");
    if(filePath.isEmpty()){
        return;
    }
    type = "sendingFile";    //设置操作类型
    handle_TextEditShowImg(":/new/icons/icons/becurrent/fileinfo.png");   //在输入框中插入图片
    emit handle_SendingFileInfoJson(friend_number,handle_FilePackageAsJSON(filePath));
}

/*  将发送的文件信息打包为Json格式
 *  path：文件路径
 *  返回值：QJsonObject(打包好的Json对象)
*/
QJsonObject FriendChat::handle_FileInfoPackageAsJSON(const QString &path)
{
    //获取文件信息
    QFileInfo info(path);
    QJsonObject dataObj;
    dataObj.insert("fileName",info.fileName());
    dataObj.insert("fileSize",info.size());
    return dataObj;
}
