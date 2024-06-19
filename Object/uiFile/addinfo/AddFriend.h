#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>

namespace Ui {
class AddFriend;
}

class AddFriend : public QWidget
{
    Q_OBJECT

public:
    ~AddFriend();
    explicit AddFriend(QWidget *parent = nullptr);

public:
    //获取好友的状态
    bool get_State();
    //初始化界面
    int init_Window();
    //设置界面查找的好友信息
    int set_AddFriendWindow(const QString& state, const QString &name, const QString &sex,
                            const QString& sign, const QString &number, const QString &headimg_Path);

private:
    QString Friend_State = " ";
    Ui::AddFriend *ui;
};

#endif // ADDFRIEND_H
