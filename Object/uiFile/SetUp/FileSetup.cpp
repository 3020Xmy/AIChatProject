#include "FileSetup.h"
#include "ui_FileSetup.h"

FileSetup::FileSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileSetup)
{
    ui->setupUi(this);
}

FileSetup::~FileSetup()
{
    delete ui;
}
