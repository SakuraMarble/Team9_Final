#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "GameModel.h"

#include <QMessageBox>
#include "QPainter"
#include "QMouseEvent"
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QDir>
#include <QFileDialog>
#include <nogo_ai.h>
#include <dialogchoosemode.h>

#include <networkdata.h>
#include <networkserver.h>
#include <networksocket.h>

#define info pair<char,int>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr,QString username = "passerby");
    ~MainWindow();
    void timer_init();//初始化计时器

private:
    Ui::MainWindow *ui;
    //DialogChooseMode* dialog;

    QTimer *timer;//计时器
    QLabel *countlabel;//倒计时label
    //QVBoxLayout *layout;
    //QWidget *centralWidget;
    QPushButton *agreeBut;
    QPushButton *disagreeBut;
    QString UserName;

    QString documentPath;
    QString subdirectory;
    QDir dir;

    GameModel *game; // 游戏指针
    GameType game_type; // 存储游戏类型

    //ai *NoGoAI;
    int lastx,lasty;
    int TimerCountNumber;
    int TimerLimit = 30;//后期可在软件内设置
    int BOARD_GRAD_SIZE = 10;

    int clickPosRow,clickPosCol; // 存储即将点击的位置
    bool selectPos = false; // 是否移动到合适的位置，以选中某个交叉点
    bool lose = false;//解决AI重开先后手问题
    bool view_lose = false;//解决复现输赢
    bool logs_empty = false;//存档文件夹是否为空
    bool online_player_flag = true;//联机对战己方持有棋子颜色
    bool online_failure = false;//联机对战己方是否失败
    bool online_agreed = false;//是否同意某客户端的联机请求
    bool online_request = false;//是否主动发起过连接

    QString opp_ip;
    quint16 opp_port = 0;
    QString IP;
    quint16 PORT;
    NetworkSocket *socket;
    NetworkServer *server;
    queue<QTcpSocket *> Clients;

    vector<vector<info>> Logs;//记录对局的数组 0为白棋 1为黑棋

    // 绘制
    void paintEvent(QPaintEvent * event);

    void initGame();
    void initGameMode(GameType type);//切换开局模式
    void reGame();//实现再来一局

    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void chessOneByPerson();
    void chessOneOnline();
    QString index_encode(int row,int col);
    pair<int,int> index_decode(QString index_data);

    void timelimit_exceeded();//超时
    void timer_update();//重新倒计时

    void ask_keeplogs();//询问是否保存对局记录
    void choose_logs();//View复现模式下选择本地存档

    void choosemode();//开局或重开选择模式&设置时间限制
private slots:
    void on_pushButton_Surrender_clicked();//认输
    void TimerCount();//一秒一刷新
    void on_pushButton_Cheating_clicked();
    void receiveData(QTcpSocket* client, NetworkData data);
    void receive_fromServer(NetworkData data);
    void displayError();
    void connected();
};


#endif // MAINWINDOW_H
