#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SignInWindow;
}

class SignInWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SignInWindow(QWidget *parent = nullptr);
    ~SignInWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SignInWindow *ui;
};

#endif // SIGNINWINDOW_H
