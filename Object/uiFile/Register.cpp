#include "Register.h"
#include "ui_Register.h"

Register::Register(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);

    init_RegisterWidget();  //初始化界面
}

Register::~Register()
{
    delete number_Validator;
    delete password_Validator;
    delete ui;
}

////------------------------------------注册模块函数-----------------------------------------------------------
/*  请求注册操作
*/
void  Register::on_register_Btn_clicked()
{
    if(!handle_getInputSecure()){   //输入不合格
        return;
    }

    //请求Login界面处理注册信息
    emit requesr_LoginHandleRegister(input_Name,input_Number,input_Sex,input_Password,input_Head);
}

/*  处理注册结果
 *  ok：注册结果
*/
int Register::handle_RegisterResult(bool ok)
{
    if(ok){     //注册成功
        QMessageBox::information(nullptr,"恭喜！","欢迎您加入QQ大家庭",QMessageBox::Ok);
        return 1;
    }else{       //用户已被注册
        QMessageBox::critical(nullptr,"提示！","账号已存在，请重新输入",QMessageBox::Ok);
        return 0;
    }
}

/*  检测用户输入是否合理
 *  返回值：bool(合理为true，不合理为false)
*/
bool Register::handle_getInputSecure()
{
    //获取输入框内容
    input_Number = ui->number_Edit->text();
    input_Password = ui->password_Edit->text();
    input_Name = ui->name_Edit->text();
    input_Sex = ui->sex_Box->currentText();

    int pos = 0;
    if(input_Name.isEmpty()){
        //检测昵称
        QMessageBox::information(nullptr,"提示","昵称为空",QMessageBox::Ok);
        return false;
    }
    else if(QValidator::Acceptable != number_Validator->validate(input_Number,pos)){
        //检测账号
        QMessageBox::information(nullptr,"提示","账号不合理!\n号码个数应为：10",QMessageBox::Ok);
        return false;
    }
    else if(QValidator::Acceptable != password_Validator->validate(input_Password,pos)){
        //检测密码
        QMessageBox::information(nullptr,"提示","密码不合理!\n号码个数应为：10-15",QMessageBox::Ok);
        return false;
    }else{
        return true;
    }
}

////------------------------------------界面控件函数-----------------------------------------------------------
/*  初始化界面
*/
int Register::init_RegisterWidget()
{
    //初始化对象
    move_Ok = false;
    input_Sex = "";
    input_Name = "";
    input_Head = "";
    input_Number = "";
    input_Password = "";

    //设置界面去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);

    //设置backimg_Lab中的gif动画
    QMovie *backimg_Gif = new QMovie(this);
    backimg_Gif->setFileName(":/new/logo/icons/logo/Register_Img.gif");
    backimg_Gif->start();
    ui->backimg_Lab->setScaledContents(true);
    ui->backimg_Lab->setMovie(backimg_Gif);

    //初始化输入验证器，限制输入为数值
    number_Validator = new QRegularExpressionValidator(QRegularExpression("\\d{10}"), this);
    password_Validator = new QRegularExpressionValidator(QRegularExpression("[A-Za-z0-9].{10,14}"), this);
    ui->number_Edit->setValidator(number_Validator);
    ui->password_Edit->setValidator(password_Validator);
    return 1;
}

/*  显示选择的头像
 *  path：头像路径
*/
int Register::handle_ShowHeadImg(QString path)
{
    input_Head = path;  //保存头像路径
    ui->headimg_Btn->setText("");
    QString str = QStringLiteral("QPushButton#headimg_Btn{ border-image: url(%1);};")
                      .arg(path);
    ui->headimg_Btn->setStyleSheet(str);
    return 1;
}

/*  选择头像函数
*/
void Register::on_headimg_Btn_clicked()
{
    HeadImg_GUI = new HeadImg(this);
    HeadImg_GUI->show();

    //显示用户选择的头像
    connect(HeadImg_GUI,&HeadImg::return_HeadimgPath,this,&Register::handle_ShowHeadImg);
}

/*  最小化界面函数
*/
void Register::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  关闭界面函数
*/
void Register::on_clos_Btn_clicked()
{
    emit handle_LoginShow();
    this->close();
}

////------------------------------------事件模块函数-----------------------------------------------------------
/*  鼠标点击事件
 *  event：事件
*/
void Register::mousePressEvent(QMouseEvent *event)
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
void Register::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

/*  鼠标释放事件
 *  event：事件
*/
void Register::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}
