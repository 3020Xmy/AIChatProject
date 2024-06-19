#include "FileInfo.h"
#include "ui_FileInfo.h"

FileInfo::FileInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileInfo)
{
    ui->setupUi(this);
}

FileInfo::~FileInfo()
{
    delete ui;
}
