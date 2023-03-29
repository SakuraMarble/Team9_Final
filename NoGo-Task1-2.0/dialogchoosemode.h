#ifndef DIALOGCHOOSEMODE_H
#define DIALOGCHOOSEMODE_H

#include <QDialog>
#include <GameModel.h>

namespace Ui {
class DialogChooseMode;
}

class DialogChooseMode : public QDialog
{
    Q_OBJECT

public:
    QString user_name = "Passerby";
    explicit DialogChooseMode(QWidget *parent = nullptr);
    ~DialogChooseMode();
    friend class MainWindow;

private slots:
    void on_pushButton_PVE_clicked();

    void on_pushButton_LocalPVP_clicked();

    void on_pushButton_OnlinePVP_clicked();

private:
    GameType game_typeForAll;
    int timelimit = 30;
    Ui::DialogChooseMode *ui;
};

#endif // DIALOGCHOOSEMODE_H