#include "mainwindow.h"

#include <QApplication>

#include <QAbstractButton>
#include <QMessageBox>
#ifndef but
#define but 3373;
QPushButton *agreeBut;
QPushButton *disagreeBut;
#endif
void MainWindow::buttonClicked(QAbstractButton *butClicked){
    if(butClicked == (QAbstractButton*)agreeBut){
        this->game->gameType=AI;
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //创建消息框
    QMessageBox MyBox(QMessageBox::Question,"","");
    MyBox.setParent(&w);
    MyBox.setWindowFlag(Qt::Dialog);
    MyBox.setWindowTitle("AI");
    MyBox.setText("是否与AI对打");
    //自定义两个按钮
    agreeBut = MyBox.addButton("同意",QMessageBox::AcceptRole);
    disagreeBut = MyBox.addButton("拒绝",QMessageBox::RejectRole);
    QObject::connect(&MyBox,&QMessageBox::buttonClicked,&w,&MainWindow::buttonClicked);

    MyBox.exec();
    return a.exec();
}
