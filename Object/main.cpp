#include <QApplication>
#include "srcFile/USER.h"
#include "uiFile/Login.h"
#include "srcFile/NetWork.h"
#include "srcFile/AiSrc/AI.h"

//全局变量的声明
AI my_AI;
USER my_USER;
NetWork my_NETWORK;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login logon_Ui;
    logon_Ui.show();
    return a.exec();
}
