#include "AiInfo.h"
#include "ui_AiInfo.h"

AiInfo::AiInfo(QWidget *parent):
    QWidget(parent),
    ui(new Ui::AiInfo)
{

    ui->setupUi(this);

    //初始化窗口
    init_AiInfoWidget();
}

/*  初始化窗口
*/
int AiInfo::init_AiInfoWidget()
{
    //初始化参数
    Chat = QSharedPointer<AiChat>(new AiChat());

    //设置头像大小自适应
    ui->Image_Lab->setScaledContents(true);

    //初始化姓名，个性签名，头像
    ui->aiName_Lab->setText(my_AI.handle_GetAiInfo(AI::aiName));
    ui->aiSign_Lab->setText(my_AI.handle_GetAiInfo(AI::aiSign));
    QPixmap originalPixmap(":/new/user/user/Ai_Logn.png");
    originalPixmap = originalPixmap.scaled(ui->Image_Lab->width(),
                                           ui->Image_Lab->height(), Qt::KeepAspectRatio);
    ui->Image_Lab->setPixmap(originalPixmap);

    connect(&my_AI, AI::new_AIInfo,this,AiInfo::set_AiInfoWidgetInfo);
    return 1;
}

AiInfo::~AiInfo()
{
    delete ui;
}

/*  设置窗口消息
*/
int AiInfo::set_AiInfoWidgetInfo()
{
    //设置参数
    ui->aiName_Lab->setText(my_AI.handle_GetAiInfo(AI::aiName));
    ui->aiSign_Lab->setText(my_AI.handle_GetAiInfo(AI::aiSign));
    return 1;
}

/*  双击机器人显示对话框
 *  event：事件
*/
void AiInfo::mouseDoubleClickEvent(QMouseEvent *event)
{
    Chat.data()->set_AiChatinAiInfo(":/new/user/user/Ai_Logn.png",
                                my_AI.handle_GetAiInfo(AI::aiName),
                                my_AI.handle_GetAiInfo(AI::aiSign));
    Chat.data()->show();
    event->accept();
}
