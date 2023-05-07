#include "Chat.h"
#include "ui_Chat.h"
#include "GameModel.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <networkserver.h>
Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{
    //qDebug() << "1" << '\n';
    //qDebug() << "2" << '\n';
    ui->setupUi(this);
    //qDebug() << "3" << '\n';
    this->setWindowTitle("Chat");
    connect(ui->btyes,&QPushButton::clicked,this,&Chat::on_pushButton_btyes_clicked);
}

Chat::~Chat()
{
    delete ui;
}
void Chat::on_pushButton_btyes_clicked(){
    QString text = this->ui->chatEdit->text();
    NetworkData chat(OPCODE::CHAT_OP,text,"");
    if (!ol_agr)
        socket->send(chat);
    else
        server->send(opponent,chat);
    qDebug() << "Client sends CHAT_OP" << '\n';
}
void Chat::setsocket(NetworkSocket *s,NetworkServer *sev,QTcpSocket *o,bool b){
    socket=s;ol_agr=b;server=sev,opponent=o;
}
