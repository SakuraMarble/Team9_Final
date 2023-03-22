#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
QPushButton *agreeBut;
QPushButton *disagreeBut;
MainWindow *MW;
void MainWindow::buttonClicked(QAbstractButton *butClicked){
    if(butClicked == (QAbstractButton*)agreeBut){
        MW->game->gameType=AI;
    }
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;MW=&w;
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
