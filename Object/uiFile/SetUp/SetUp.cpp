#include "SetUp.h"
#include "ui_SetUp.h"

SetUp::SetUp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetUp)
{
    ui->setupUi(this);

    //初始化界面
    initSetUp_Boundary();
}

SetUp::~SetUp()
{
    delete AiSetup_GUI;
    delete UserSetup_GUI;
    delete FileSetup_GUI;
    delete ui;
}

////------------------------------------事件模块函数-------------------------------------------------------------
/*  鼠标点击事件
 *  event：事件
*/
void SetUp::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        move_Ok = true;
        this->setMouseTracking(true);   //开启鼠标追踪
        move_point = event->pos();      //获取鼠标位置
    }
}

/*  鼠标释放事件
 *  event：事件
*/
void SetUp::mouseReleaseEvent(QMouseEvent *event)
{
    move_Ok = false;
}

/*  鼠标移动事件
 *  event：事件
*/
void SetUp::mouseMoveEvent(QMouseEvent *event)
{
    if(move_Ok){
        QPoint move_pos = event->globalPos();   //获取当前位置
        this->move(move_pos - move_point);
    }
}

////------------------------------------界面模块函数-------------------------------------------------------------
/*  初始化界面
*/
int SetUp::initSetUp_Boundary()
{
    //初始化Ai设置界面
    init_AiSetUp();

    UserSetup_GUI = new UserSetup(ui->rightWidget);
    FileSetup_GUI = new FileSetup();

    //设置界面透明与去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);
    UserSetup_GUI->show();

    //设置backimg_Lab中的gif动画
    QMovie *backimg_Gif = new QMovie(this);
    backimg_Gif->setFileName(":/new/logo/icons/logo/Register_Img.gif");
    backimg_Gif->start();
    ui->img_Lab->setScaledContents(true);
    ui->img_Lab->setMovie(backimg_Gif);
    return 1;
}

/*  关闭界面函数
*/
void SetUp::on_clos_Btn_clicked()
{
    this->close();
}

/*  最小化界面函数
*/
void SetUp::on_reduce_Btn_clicked()
{
    this->showMinimized();
}

/*  用户设置界面函数
*/
void SetUp::on_userSetup_Btn_clicked()
{
    //设置其他界面不可见
    AiSetup_GUI->hide();
    FileSetup_GUI->hide();

    UserSetup_GUI->show();
}

/*  文件设置界面函数
*/
void SetUp::on_fileSetup_Btn_clicked()
{
    FileSetup_GUI->setParent(ui->rightWidget);        //使rightWidget中显示FileSetup_GUI

    //设置其他界面不可见
    AiSetup_GUI->hide();
    UserSetup_GUI->hide();

    FileSetup_GUI->show();
}

////------------------------------------AI模块函数-------------------------------------------------------------
/*  初始化Ai设置界面
*/
int SetUp::init_AiSetUp()
{
    //初始化对象
    AiSetup_GUI = new AiSetup();
    //请求设置Ai信息
    connect(AiSetup_GUI,&AiSetup::set_AiInfo,this,&SetUp::request_SetAiInfo);
    //请求获取Ai信息
    connect(AiSetup_GUI,&AiSetup::get_AiInfo,this,&SetUp::request_GetAiInfo);
    return 1;
}

/*  显示Ai设置界面
*/
void SetUp::on_AiSetup_Btn_clicked()
{
    AiSetup_GUI->setParent(ui->rightWidget);

    //设置其他界面不可见
    FileSetup_GUI->hide();
    UserSetup_GUI->hide();

    AiSetup_GUI->get_InitAiInfo();
    AiSetup_GUI->show();
}

/*  请求设置Ai信息
 *  type：操作类型
*/
int SetUp::request_SetAiInfo(const QString &type)
{
    emit relay_UserWidgetSetAiInfo(type);      //转发至用户界面提醒设置Ai信息
    return 1;
}

/*  请求获取Ai信息
 *  type：操作类型
*/
int SetUp::request_GetAiInfo(const QString &type)
{
    emit relay_UserWidgetGetAiInfo(type);      //转发至用户界面提醒获取Ai信息
    return 1;
}
