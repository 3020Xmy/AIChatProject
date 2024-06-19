#ifndef FILEINFO_H
#define FILEINFO_H

#include <QWidget>

namespace Ui {
class FileInfo;
}

class FileInfo : public QWidget
{
    Q_OBJECT

public:
    explicit FileInfo(QWidget *parent = nullptr);
    ~FileInfo();

private:
    Ui::FileInfo *ui;
};

#endif // FILEINFO_H
