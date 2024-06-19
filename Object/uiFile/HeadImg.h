#ifndef HEADIMG_H
#define HEADIMG_H

#include <QMovie>
#include <QWidget>

namespace Ui {
class HeadImg;
}

class HeadImg : public QWidget
{
    Q_OBJECT

public:
    explicit HeadImg(QWidget *parent = nullptr);
    ~HeadImg();

public:
    //初始化界面
    int init_HeadImgWidget();

signals:
    //返回头像路径
    void return_HeadimgPath(QString path);

private slots:
    //点击头像，返回对应的图片路径
    void on_exit_Btn_clicked();
    void on_img1_Btn_clicked();
    void on_img2_Btn_clicked();
    void on_img3_Btn_clicked();
    void on_img4_Btn_clicked();
    void on_img5_Btn_clicked();
    void on_img6_Btn_clicked();
    void on_img7_Btn_clicked();
    void on_img8_Btn_clicked();

private:
    Ui::HeadImg *ui;
};

#endif // HEADIMG_H
