#include "dialogchoosemode.h"
#include "ui_dialogchoosemode.h"
#include "GameModel.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QPixmap>

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
    QString str = ui->plainTextEdit->toPlainText();
    if (!str.isEmpty()) {
        bool ok;
        str.toInt(&ok);
        if (ok)
            timelimit = str.toInt();
    }
    MainWindow *w = new MainWindow(nullptr,this);
    w->show();
}



void DialogChooseMode::on_pushButton_LocalPVP_clicked()
{
    hide();
    game_typeForAll = MAN;
    QString str = ui->plainTextEdit->toPlainText();
    if (!str.isEmpty()) {
        bool ok;
        str.toInt(&ok);
        if (ok)
            timelimit = str.toInt();
    }
    MainWindow *w = new MainWindow(nullptr,this);
    w->show();
}



void DialogChooseMode::on_pushButton_OnlinePVP_clicked()
{
    QMessageBox *warning = new QMessageBox(this);
    warning->warning(this,"Sorry","We're still designing this part!");
    delete warning;
}

