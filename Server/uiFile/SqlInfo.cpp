#include "SqlInfo.h"
#include "ui_SqlInfo.h"

SqlInfo::SqlInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SqlInfo)
{
    ui->setupUi(this);

}

SqlInfo::~SqlInfo()
{
    delete ui;
}
