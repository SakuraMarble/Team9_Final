#ifndef W_CHANGEMODE_H
#define W_CHANGEMODE_H

#include <QDialog>

namespace Ui {
class w_ChangeMode;
}

class w_ChangeMode : public QDialog
{
    Q_OBJECT

public:
    explicit w_ChangeMode(QWidget *parent = nullptr);
    ~w_ChangeMode();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::w_ChangeMode *ui;
};

#endif // W_CHANGEMODE_H
