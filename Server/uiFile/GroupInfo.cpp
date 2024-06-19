#include "GroupInfo.h"
#include "ui_GroupInfo.h"

GroupInfo::GroupInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupInfo)
{
    ui->setupUi(this);
}

GroupInfo::~GroupInfo()
{
    delete ui;
}
