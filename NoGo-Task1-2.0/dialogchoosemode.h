#ifndef DIALOGCHOOSEMODE_H
#define DIALOGCHOOSEMODE_H

#include <QDialog>

namespace Ui {
class DialogChooseMode;
}

class DialogChooseMode : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChooseMode(QWidget *parent = nullptr);
    ~DialogChooseMode();

private slots:
    void on_pushButton_PVE_clicked();

    void on_pushButton_LocalPVP_clicked();

    void on_pushButton_OnlinePVP_clicked();

private:
    Ui::DialogChooseMode *ui;
};

#endif // DIALOGCHOOSEMODE_H
