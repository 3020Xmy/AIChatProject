#include "HeadImg.h"
#include "ui_HeadImg.h"

HeadImg::HeadImg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeadImg)
{
    ui->setupUi(this);

    //初始化界面
    init_HeadImgWidget();
}

HeadImg::~HeadImg()
{
    delete ui;
}

/*  初始化界面
*/
int HeadImg::init_HeadImgWidget()
{
    setWindowFlags(Qt::WindowType::FramelessWindowHint);    //去掉边框

    //设置back_Lab中的gif动画
    QMovie *backimg_Gif = new QMovie(this);
    backimg_Gif->setFileName(":/new/logo/icons/logo/Register_Img.gif");
    backimg_Gif->start();
    ui->back_Lab->setScaledContents(true);
    ui->back_Lab->setMovie(backimg_Gif);
    return 1;
}

void HeadImg::on_exit_Btn_clicked()
{
    emit return_HeadimgPath(":/new/user/user/My.jpg");
    this->close();
}

void HeadImg::on_img1_Btn_clicked()
{
    emit return_HeadimgPath(":/new/user/user/My.jpg");
    this->close();
}


void HeadImg::on_img2_Btn_clicked()
{
    emit return_HeadimgPath(":/new/user/user/headImg_1.jpg");
    this->close();
}


void HeadImg::on_img3_Btn_clicked()
{
    emit return_HeadimgPath(":/new/user/user/headImg_2.jpg");
    this->close();
}


void HeadImg::on_img4_Btn_clicked()
{
    emit return_HeadimgPath(":/new/user/user/headImg_3.jpg");
    this->close();
}


void HeadImg::on_img5_Btn_clicked()
{
    emit return_HeadimgPath(":/new/user/user/headImg_4.jpg");
    this->close();
}


void HeadImg::on_img6_Btn_clicked()
{
    emit return_HeadimgPath(":/new/user/user/headImg_5.jpg");
    this->close();
}


void HeadImg::on_img7_Btn_clicked()
{
    emit return_HeadimgPath(":/new/user/user/headImg_6.jpg");
    this->close();
}


void HeadImg::on_img8_Btn_clicked()
{
    emit return_HeadimgPath(":/new/user/user/headImg_8.jpg");
    this->close();
}

