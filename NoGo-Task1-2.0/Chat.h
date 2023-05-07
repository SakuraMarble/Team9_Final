#ifndef CHAT_H
#define CHAT_H

#include <QDialog>
#include <GameModel.h>
#include <connectdialog.h>
#include <networksocket.h>
#include <networkserver.h>
namespace Ui {
class Chat;
}

class Chat : public QDialog
{
    Q_OBJECT

public:
    QString user_name = "Passerby";
    explicit Chat(QWidget *parent = nullptr);
    ~Chat();
    friend class MainWindow;
    void setsocket(NetworkSocket *s,NetworkServer *sev,QTcpSocket *o,bool b);
private slots:
    void on_pushButton_btyes_clicked();

private:
    Ui::Chat *ui;
    NetworkSocket *socket;

    QTcpSocket *opponent;
    NetworkServer *server;
    bool ol_agr;
};

#endif // CHAT_H
