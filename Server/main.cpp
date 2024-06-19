#include <QApplication>
#include "uiFile/mainWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWidget w;
    w.show();
    return a.exec();
}
