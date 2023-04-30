#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QWidget>
#include <QLineEdit>
#include <QButtonGroup>
#include <QRadioButton>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QIntValidator>
#include <QGridLayout>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = nullptr);
    ~ConnectDialog();
    QString get_ip() const;
    quint16 get_port() const;
    bool get_hold() const;

private slots:
    void on_pushButton_clicked();

private:
    QLineEdit *ipLineEdit;
    QLineEdit *portLineEdit;
    QButtonGroup *colorGroup;
    QRadioButton *blackRadio;
    QRadioButton *whiteRadio;
    QPushButton *connectButton;

    QString ip;
    quint16 port;
    bool online_hold = true;

private:
    Ui::ConnectDialog *ui;
};

#endif // CONNECTDIALOG_H
