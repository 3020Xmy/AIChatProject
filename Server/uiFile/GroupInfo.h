#ifndef GROUPINFO_H
#define GROUPINFO_H

#include <QWidget>

namespace Ui {
class GroupInfo;
}

class GroupInfo : public QWidget
{
    Q_OBJECT

public:
    explicit GroupInfo(QWidget *parent = nullptr);
    ~GroupInfo();

private:
    Ui::GroupInfo *ui;
};

#endif // GROUPINFO_H
