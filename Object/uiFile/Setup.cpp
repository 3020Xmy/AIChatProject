#include "Setup.h"
#include "ui_Setup.h"

Setup::Setup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setup)
{
    ui->setupUi(this);

    //设置界面透明与去掉边框
    setWindowFlags(Qt::WindowType::FramelessWindowHint);

}

Setup::~Setup()
{
    delete ui;
}
