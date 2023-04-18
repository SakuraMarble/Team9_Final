#include "signinwindow.h"
#include <QApplication>

#include <QAbstractButton>
#include <QMessageBox>
#ifndef but
#define but 3373;

#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    SignInWindow w;
    w.show();

    return a.exec();
}
