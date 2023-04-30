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
}

void DialogChooseMode::on_pushButton_View_clicked()
{
    hide();
    game_typeForAll = View;
}

void DialogChooseMode::on_pushButton_LocalPVP_clicked()
{
    hide();
    game_typeForAll = MAN;
    QString str = ui->plainTextEdit->toPlainText();
    //QString str_size = ui->plainTextEdit_2->toPlainText();
    if (!str.isEmpty()) {
        bool ok;
        str.toInt(&ok);
        if (ok)
            timelimit = str.toInt();
    }
    /*if (!str_size.isEmpty()) {
        bool ok;
        str_size.toInt(&ok);
        if (ok)
            pvp_boardsize = str_size.toInt() + 1;
    }*/
}



void DialogChooseMode::on_pushButton_OnlinePVP_clicked()
{
    /*QMessageBox *warning = new QMessageBox(this);
    warning->warning(this,"Sorry","We're still designing this part!");
    delete warning;*/
    hide();
    ConnectDialog *dialog = new ConnectDialog(this);
    dialog->exec();
    ip = dialog->get_ip();
    port = dialog->get_port();
    online_hold = dialog->get_hold();
    cout << online_hold << endl;
    game_typeForAll = Online;
    delete dialog;

}


void DialogChooseMode::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0)
     pvp_boardsize = 15;
    if(index == 1)
        pvp_boardsize = 12;
    if(index == 2)
        pvp_boardsize = 14;
}

