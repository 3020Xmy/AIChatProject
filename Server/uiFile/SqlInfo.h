#ifndef SQLINFO_H
#define SQLINFO_H

#include <QWidget>

namespace Ui {
class SqlInfo;
}

class SqlInfo : public QWidget
{
    Q_OBJECT

public:
    explicit SqlInfo(QWidget *parent = nullptr);
    ~SqlInfo();


private:
    Ui::SqlInfo *ui;
};

#endif // SQLINFO_H
