#include "dialogchoosemode.h"
#include "ui_dialogchoosemode.h"
#include "GameModel.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
GameType game_typeForAll;
DialogChooseMode::DialogChooseMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChooseMode)
{
    ui->setupUi(this);
    this->setWindowTitle("Choose Your Mode");
    QPixmap pic(":/img/img/Bochii.jpg");
    ui->label_Bochii->setPixmap(pic.scaled(180,180));
}

DialogChooseMode::~DialogChooseMode()
{
    delete ui;
}

void DialogChooseMode::on_pushButton_PVE_clicked()
{
    hide();
    game_typeForAll = AI;
    MainWindow *w = new MainWindow();
    w->show();
}



void DialogChooseMode::on_pushButton_LocalPVP_clicked()
{
    hide();
    game_typeForAll = MAN;
    MainWindow *w = new MainWindow();
    w->show();
}



void DialogChooseMode::on_pushButton_OnlinePVP_clicked()
{
    QMessageBox *warning = new QMessageBox(this);
    warning->warning(this,"Sorry","We're still designing this part!");
    delete warning;
}

