#ifndef FILESETUP_H
#define FILESETUP_H

#include <QWidget>

namespace Ui {
class FileSetup;
}

class FileSetup : public QWidget
{
    Q_OBJECT

public:
    explicit FileSetup(QWidget *parent = nullptr);
    ~FileSetup();

private:
    Ui::FileSetup *ui;
};

#endif // FILESETUP_H
