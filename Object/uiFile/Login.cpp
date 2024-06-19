#include "Login.h"
#include "ui_Login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    init_TcpModule();   //初始化Tcp模块
    init_LoginWidget(); //初始化界面
    init_Settings();    //初始化默认配置
}

Login::~Login()
{
    delete settings;
    delete animation;
    delete usernumber_Validator;
    delete password_Validator;
    delete ui;
}

////------------------------------------注册模块函数-----------------------------------------------------------
/*  处理注册申请
 *  name：用户昵称   number：用户账号     sex：用户性别    password：用户密码   path：用户头像
*/
int Login::handle_RegisterPackageAsJSON(QString name, QString number, QString sex,
                                        QString password, QString path)
{
    //将发送的数据打包为Json格式
    QJsonObject Json;
    Json.insert("type","register");
    QJsonObject dataObj;
    dataObj.insert("userSex",sex);
    dataObj.insert("userSign"," ");
    dataObj.insert("userName",name);
    dataObj.insert("userNumber",number);
    dataObj.insert("userHeadimg",path);
    dataObj.insert("userEncrypt"," ");
    dataObj.insert("userPassword",password);
    Json.insert("data",dataObj);

    //将Json格式转换为Byte格式
    QJsonDocument jsonDoc(Json);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
    tcpThread_Obj->sending_ToServer(byteArray);       //设置发送的数据
    return 1;
}

/*  注册账号
*/
void Login::on_register_Btn_clicked()
{
    Register_GUI = new Register();
    //关闭Register界面后显示Login界面
    connect(Register_GUI,&Register::handle_LoginShow,this,&Login::handle_ShowLoginWidget);
    //请求Login界面处理注册信息
    connect(Register_GUI,&Register::requesr_LoginHandleRegister,this,&Login::handle_RegisterPackageAsJSON);
    //转发注册结果至注册界面
    connect(this,&Login::request_LoginHandleRegisterResult,Register_GUI,&Register::handle_RegisterResult);
    Register_GUI->show();
    this->showMinimized();
}

/*  验证窗口输入
 *  返回值：bool(正确返回true，错误返回false)
*/
bool Login::handle_InputResult()
{
    int pos = 0;
    if(QValidator::Acceptable != usernumber_Validator->validate(input_Usernumber,pos) ||
            input_Usernumber == nullptr){
        //验证号码是否存在且正确
        QMessageBox::information(nullptr,"提示","账号错误!",QMessageBox::Ok);
        return false;
    }
    else if(QValidator::Acceptable != password_Validator->validate(input_Password,pos) ||
            input_Password == nullptr){
        //验证密码是否正确
        QMessageBox::information(nullptr,"提示","密码错误！",QMessageBox::Ok);
        return false;
    }else{
        return true;
    }
}

/*  转发注册结果至Login界面
 *  ok：注册结果
*/
void Login::relay_RegisterResult(bool ok)
{
    emit request_LoginHandleRegisterResult(ok);    //请求处理注册结果
}

////--------------------------------------------应用配置函数-------------------------------------------------
/*  初始化默认配置
*/
int Login::init_Settings()
{
    //读取配置文件
    get_Settings();

    if(saved_Password){
        //保存密码
        ui->saved_Password->setChecked(saved_Password);
        ui->password_Edit->setText(input_Password);
    }

    if(saved_Usernumbe){
        //保存账号
        ui->saved_number->setChecked(saved_Usernumbe);
        ui->usernumber_Box->addItem(input_Usernumber);
    }
    return 1;
}

/*  读取设置文件
*/
int Login::get_Settings()
{
    input_Password = settings->value("Password","").toString();              //读取密码
    input_Usernumber = settings->value("Username","").toString();            //读取账号
    encrypt_Password = settings->value("encrypt_Pswd","").toString();        //读取加密的密码
    saved_Password = settings->value("saved_Password",false).toBool();
    saved_Usernumbe = settings->value("saved_Usernumbe",false).toBool();
    return 1;
}

/*  修改设置文件
*/
int Login::set_Settings()
{
    get_EncryptData(input_Password);                            //密码加密
    settings->setValue("Password",input_Password);          //密码
    settings->setValue("Username",input_Usernumber);        //用户名
    settings->setValue("encrypt_Pswd",encrypt_Password);    //加密的密码
    settings->setValue("saved_Password",saved_Password);    //是否保存密码
    settings->setValue("saved_Usernumbe",saved_Usernumbe);  //是否保存账号
    settings->sync();
    return 1;
}

////------------------------------------登录模块函数-----------------------------------------------------------
/*  初始化用户界面
 *  ok：返回结果    code：信息编码    sex：用户性别    name：用户昵称    sign：用户个签
 *  number：用户账号    headimg：用户头像
*/
int Login::handle_InitUserInfoWidget(bool ok, const QString &code, const QString &sex,
                                     const QString &name, const QString &sign, const QString &number,
                                     const QString headimg)
{
    if(ok){
        if(code == "1"){
            //记住密码操作
            if(saved_Password){
                //记住密码：把加密的密码上传到服务器
                get_EncryptData(input_Password);

                //将加密请求发送的数据打包为Json格式
                handle_EncryptPackageAsJSON();
            }
            set_Settings();     //更新配置文件
            set_Animation(headimg);    //登录动画
            my_USER.set_AllObject(sex,name,sign,number,headimg); //初始化用户界面
            return 1;
        }else{
            QMessageBox::information(nullptr,"提示","用户已登录，请勿重复登录！",QMessageBox::Ok);
            return 0;
        }
    }else{
        QMessageBox::information(nullptr,"提示","用户信息异常或不存在该用户！",QMessageBox::Ok);
        return -1;
    }
}

/*  初始化登录操作
*/
void Login::on_logon_Btn_clicked()
{
    //获取输入框内容
    input_Usernumber = ui->usernumber_Box->currentText();
    input_Password = ui->password_Edit->text();

    if(!handle_InputResult()){     //验证输入信息
        return;
    }

    //将登录请求发送的数据打包为Json格式
    handle_LoginRequestPackageAsJSON();
}

/*  将登录数据打包为Json格式
*/
int Login::handle_LoginRequestPackageAsJSON()
{
    //将发送的数据打包为Json格式
    QJsonObject Json;
    Json.insert("type","login");
    QJsonObject dataObj;
    dataObj.insert("userNumber",input_Usernumber);
    dataObj.insert("userPassword",input_Password);
    Json.insert("data",dataObj);

    //将Json格式转换为Byte格式
    QJsonDocument jsonDoc(Json);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
    tcpThread_Obj->sending_ToServer(byteArray);      //设置发送的数据
    return 1;
}

/*  初始化好友界面
 *  name：用户昵称    sign：用户个签    number：用户账号    headimg：用户头像     state：用户状态
*/
int Login::request_InitFriendInfoWidget(const QString &name, const QString &sign, const QString &number,
                                        const QString headimg, const QString &state)
{
    UserInfo_GUI->add_InitFriendInfoWidget(name,sign,number,headimg,state);
    return 1;
}

/*  初始化群聊界面
 *  name：群聊昵称    id：群聊ID    headimg：群聊头像
*/
int Login::request_InitGroupInfoWidget(const QString &name, const QString &id, const QString headimg)
{
    UserInfo_GUI->add_InitGroupInfoWidget(name,id,headimg);
    return 1;
}

////------------------------------------加密模块函数-----------------------------------------------------------
/*  将加密数据打包为Json格式
*/
int Login::handle_EncryptPackageAsJSON()
{
    //将发送的数据打包为Json格式
    QJsonObject Json;
    Json.insert("type","encrypt");
    QJsonObject dataObj;
    dataObj.insert("userNumber",input_Usernumber);
    dataObj.insert("userEncrypt",encrypt_Password);
    Json.insert("data",dataObj);

    //将Json格式转换为Byte格式
    QJsonDocument jsonDoc(Json);
    QByteArray byteArray = jsonDoc.toJson(QJsonDocument::Compact);
    tcpThread_Obj->sending_ToServer(byteArray);    //设置发送的数据
    return 1;
}

/*  获取加密后的数据
 *  str：原数据
*/
int Login::get_EncryptData(const QString &str)
{
    QByteArray btArray= str.toLocal8Bit();  //字符串转换为字节数组数据
    QCryptographicHash hash(QCryptographicHash::Md5);  //Md5加密算法
    hash.addData(btArray);  //添加数据到加密哈希值
    QByteArray resultArray = hash.result();  //返回最终的哈希值
    encrypt_Password = resultArray.toHex();  //转换为16进制字符串
    return 1;
}

/*  处理加密请求返回的结果
*/
int Login::handle_EncryptResult(const bool &ok,const QString &code)
{
    if(!ok){
        QMessageBox::information(nullptr,"提示","记住密码失败！",QMessageBox::Ok);
        return 0;
    }
    else{
        return 1;
    }
}

/*  记住账号
 *  checked：状态位
*/
void Login::on_saved_number_clicked(bool checked)
{
    saved_Usernumbe = checked;
}


/*  记住密码
 *  checked：状态位
*/
void Login::on_saved_Password_clicked(bool checked)
{
    saved_Password = checked;
}

////------------------------------------Tcp模块函数-----------------------------------------------------------
/*  初始化Tcp模块)
*/
int Login::init_TcpModule()
{
    tcpThread_Obj = new TcpThread(new QTcpSocket()); //定义处理Json线程
    init_TcpConnect();     //初始化Tcp线程连接
    handle_StartTcpThread();  //启动线程
    return 1;
}

/*  初始化Tcp线程连接
*/
int Login::init_TcpConnect()
{
    //请求关闭线程
    connect(this,&Login::handle_TcpThreadClose,tcpThread_Obj,&TcpThread::handle_CloseThread);
    //转发注册结果至注册界面
    connect(tcpThread_Obj,&TcpThread::return_RegisterResult,this,&Login::relay_RegisterResult);
    //登录后初始化用户界面
    connect(tcpThread_Obj,&TcpThread::return_UserInfo,this,&Login::handle_InitUserInfoWidget);
    //登录后初始化群聊信息
    connect(tcpThread_Obj,&TcpThread::return_GroupInfo,this,&Login::request_InitGroupInfoWidget);
    //登录后初始化好友信息
    connect(tcpThread_Obj,&TcpThread::return_FriendInfo,this,&Login::request_InitFriendInfoWidget);
    //记住账号密码后处理加密结果
    connect(tcpThread_Obj,&TcpThread::return_SaveEncryptResult,this,&Login::handle_EncryptResult);
    return 1;
}

/*  启动Tcp线程
*/
int Login::handle_StartTcpThread()
{
    QThreadPool::globalInstance()->start(tcpThread_Obj);//启动线程
    return 1;
}

////----------------------------------------事件模块函数------------------------------------------------------
/*  鼠标点击事件
 *  event：事件
*/
void Login::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

/*  鼠标移动事件
 *  event：事件
*/
void Login::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

/*  鼠标释放事件
 *  event：事件
*/
void Login::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

////-----------------------------------------界面控件函数----------------------------------------------------
/*  绘制登录动画，显示用户信息界面
 *  headimg：用户头像
*/
int Login::set_Animation(const QString& headimg)
{
    init_UserHeadImg(headimg);  //设置用户头像
    //设置控件不可见
    ui->usernumber_Box->hide();
    ui->password_Edit->hide();
    ui->saved_number->hide();
    ui->saved_Password->hide();
    ui->register_Btn_2->hide();
    ui->logon_Btn->hide();
    ui->register_Btn->hide();
    animation->start();     //执行GUI动画

    if(UserInfo_GUI != nullptr){
        delete UserInfo_GUI;
    }
    QObject::disconnect(tcpThread_Obj);     //断开所有信号槽
    UserInfo_GUI = new UserInfo(tcpThread_Obj);
    return 1;
}

/*  初始化界面
*/
int Login::init_LoginWidget()
{
    //初始化参数
    move_Ok = false;
    input_Password = "";
    input_Usernumber = "";
    saved_Password = false;
    UserInfo_GUI = nullptr;
    saved_Usernumbe = false;

    settings = new QSettings("QQ-Qt", "Wild_Pointer");     //设置应用名称
    setWindowFlags(Qt::WindowType::FramelessWindowHint);   //去掉边框
    init_UserHeadImg(":/new/Chat/icons/Chat/logo_Show.png");    //设置初始头像
    ui->usernumber_Box->lineEdit()->setPlaceholderText("QQ号码/手机/邮箱");   //设置username_Box提示

    //设置Top中的gif动画
    QMovie *top_Gif = new QMovie(this);
    top_Gif->setFileName(":/new/logo/icons/logo/Top.gif");
    top_Gif->start();
    ui->Top->setMovie(top_Gif);

    //设置登录动画
    animation = new QPropertyAnimation(ui->user_image, "geometry");//设置user_image的位置大小
    animation->setDuration(600);                      //设置动画完成为600毫秒
    animation->setStartValue(QRect(160, 90, 85, 85));  //设置动画初始位置值
    animation->setEndValue(QRect(160, 175, 85, 85));   //设置动画结束位置值
    connect(animation, &QPropertyAnimation::finished,this,&Login::handle_closeWidget);

    //初始化输入验证器，限制输入为数值
    usernumber_Validator = new QRegularExpressionValidator(QRegularExpression("\\d{10}"), this);
    password_Validator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z0-9].{10,14}"), this);
    ui->usernumber_Box->setValidator(usernumber_Validator);
    ui->password_Edit->setValidator(password_Validator);
    return 1;
}

/*  设置用户头像
 *  headimg：用户头像
*/
int Login::init_UserHeadImg(const QString& headimg)
{
    //设置user_image为圆形
    QPixmap pixmap(headimg);
    pixmap = pixmap.scaled(ui->user_image->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap roundPixmap(ui->user_image->size());
    roundPixmap.fill(Qt::transparent);
    QPainter painter(&roundPixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(roundPixmap.rect());
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawPixmap(0, 0, pixmap);
    ui->user_image->setPixmap(roundPixmap);
}

/*  处理登录后关闭界面
*/
int Login::handle_closeWidget()
{
    QTimer::singleShot(1000, this,&Login::handle_ShowUserInfoWidget);
}

/*  显示UserInfo界面
*/
int Login::handle_ShowUserInfoWidget()
{
    this->close();
    UserInfo_GUI->show();
    return 1;
}

/*  显示界面
*/
int Login::handle_ShowLoginWidget()
{
    this->showNormal();
    return 1;
}

/*  关闭界面函数
*/
void Login::on_clos_Btn_clicked()
{
    this->close();
    emit handle_TcpThreadClose(" ");  //请求关闭线程
}

/*  最小化界面函数
*/
void Login::on_reduce_Btn_clicked()
{
    this->showMinimized();
}
