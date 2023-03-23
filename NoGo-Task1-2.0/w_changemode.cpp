#include "w_changemode.h"
#include "ui_w_changemode.h"
#include "QPixmap"
#include "GameModel.h"
#include "QDebug"
GameType game_typeForAll;

w_ChangeMode::w_ChangeMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::w_ChangeMode)
{
    ui->setupUi(this);
    this->setWindowTitle("NoGo Made by Team 9");
    QPixmap pic1(":/new/prefix1/MBJ.jpg");
    QPixmap pic2(":/new/prefix1/LYC.png");
    QPixmap pic3(":/new/prefix1/ZK.jpg");
    QPixmap pic4(":/new/prefix1/NoGo.png");
    ui->label->setPixmap(pic1.scaled(100,100));
    ui->label_2->setPixmap(pic2.scaled(110,110));
    ui->label_3->setPixmap(pic3.scaled(105,105));
    ui->label_5->setPixmap(pic4.scaled(200,100));
}

w_ChangeMode::~w_ChangeMode()
{
    delete ui;
}

void w_ChangeMode::on_pushButton_clicked()
{
    game_typeForAll = MAN;
    qDebug()<<"now game_type is"<<game_typeForAll;
    this->close();

}


void w_ChangeMode::on_pushButton_2_clicked()
{
    game_typeForAll = AI;
    qDebug()<<"now game_type is"<<game_typeForAll;
    this->close();
}

