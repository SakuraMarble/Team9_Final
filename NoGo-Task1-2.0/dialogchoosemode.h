#ifndef DIALOGCHOOSEMODE_H
#define DIALOGCHOOSEMODE_H

#include "qevent.h"
#include <QDialog>
#include <GameModel.h>
#include <connectdialog.h>
#include <QApplication>

namespace Ui {
class DialogChooseMode;
}

class DialogChooseMode : public QDialog
{
    Q_OBJECT

public:
    QString user_name = "Passerby";
    explicit DialogChooseMode(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event) override
    {
        event->accept();
        QApplication::closeAllWindows();
        QCoreApplication::quit();
    }
    ~DialogChooseMode();
    friend class MainWindow;

private slots:
    void on_pushButton_PVE_clicked();

    void on_pushButton_LocalPVP_clicked();

    void on_pushButton_OnlinePVP_clicked();


    void on_pushButton_View_clicked();

    void on_comboBox_currentIndexChanged(int index);


private:
    GameType game_typeForAll;
    int pvp_boardsize = 10;
    int timelimit = 30;
    QString ip;
    quint16 port;
    bool online_hold = true;
    Ui::DialogChooseMode *ui;
};

#endif // DIALOGCHOOSEMODE_H
