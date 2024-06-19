#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QWidget>

namespace Ui {
class AddGroup;
}

class AddGroup : public QWidget
{
    Q_OBJECT

public:
    ~AddGroup();
    explicit AddGroup(QWidget *parent = nullptr);
public:
    //设置界面查找的群聊信息
    int set_AddGroupWindow(const QString &number, const QString &name, const QString &headimg_Path);

private:
    Ui::AddGroup *ui;
};

#endif // ADDGROUP_H
