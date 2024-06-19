#include "AiSetup.h"
#include "ui_AiSetup.h"

AiSetup::AiSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AiSetup)
{
    ui->setupUi(this);

    //设置控件信息
    set_AiWidgetInfo();

    //初始化验证器
    aiName_Validator = new QRegularExpressionValidator(QRegularExpression("^.{8}$"));
    aiSign_Validator = new QRegularExpressionValidator(QRegularExpression("^.{15}$"));

    //设置验证器
    ui->Ainame_Edit->setValidator(aiName_Validator);
    ui->Aisign_Edit->setValidator(aiSign_Validator);

    connect(&my_AI,AI::new_AIInfo,this,AiSetup::set_AiWidgetInfo);
}

AiSetup::~AiSetup()
{
    delete aiName_Validator;
    delete aiSign_Validator;
    delete ui;
}

////------------------------------------AI模块函数-------------------------------------------------------------
/*  设置控件信息
*/
int AiSetup::set_AiWidgetInfo()
{
    //设置控件消息
    ui->Ainame_Edit->setText(my_AI.handle_GetAiInfo(AI::aiName));
    ui->Aisign_Edit->setText(my_AI.handle_GetAiInfo(AI::aiSign));
    ui->APIKey_Edit->setText(my_AI.handle_GetAiInfo(AI::aiAPIKey));
    ui->APISecret_Edit->setText(my_AI.handle_GetAiInfo(AI::aiAPISecret));
    return 1;
}

/*  请求获取Ai信息
*/
int AiSetup::get_InitAiInfo()
{
    emit get_AiInfo("getAI");    //请求获取Ai信息
    return 1;
}

/*  确定修改信息
*/
int AiSetup::on_determine_Btn_clicked()
{
    my_AI.handle_SetAllObject(ui->Ainame_Edit->text(),ui->Aisign_Edit->text(),
                              ui->APIKey_Edit->text(),ui->APISecret_Edit->text());
    set_AiWidgetInfo();       //设置组件显示信息
    emit set_AiInfo("setAI");    //请求设置Ai信息
    QMessageBox::information(nullptr,"提示","已设置AI信息",QMessageBox::Ok);
    return 1;
}


