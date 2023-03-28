#include "signinwindow.h"
#include "ui_signinwindow.h"
#include "dialogchoosemode.h"
#include <mainwindow.h>
#include <QMessageBox>
#include <QString>
#include <QShortcut>

SignInWindow::SignInWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SignInWindow)
{
    ui->setupUi(this);
    setWindowTitle("NoGo");
    QShortcut *key=new QShortcut(QKeySequence(Qt::Key_Return),this);//创建一个快捷键"Key_Return"键

    connect(key,SIGNAL(activated()),this,SLOT(on_pushButton_clicked()));//连接到指定槽函数
}

SignInWindow::~SignInWindow()
{
    delete ui;
}

void SignInWindow::on_pushButton_clicked()
{
    if((ui->lineEdit_UserName->text() == "test" && ui->lineEdit_Password->text() == "test" )||
            (ui->lineEdit_UserName->text() == "team9" && ui->lineEdit_Password->text() == "lycggisgreat"))
    {
        hide();
        MainWindow *w = new MainWindow(nullptr,ui->lineEdit_UserName->text());
        w->show();
        /***
        DialogChooseMode w;
        w.user_name = ui->lineEdit_UserName->text();
        w.exec();
        ***/
    } else {
        QMessageBox *warning = new QMessageBox(this);
        warning->warning(this,"Warning","The UserName or Password is wrong");
        delete warning;
    }
}

