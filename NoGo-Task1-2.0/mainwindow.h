#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "GameModel.h"

#include <QMessageBox>
#include "QPainter"
#include "QMouseEvent"
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <nogo_ai.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void timer_init();//初始化计时器

private:
    Ui::MainWindow *ui;

    QTimer *timer;//计时器
    QLabel *countlabel;//倒计时label
    //QVBoxLayout *layout;
    //QWidget *centralWidget;
    QPushButton *agreeBut;
    QPushButton *disagreeBut;

    GameModel *game; // 游戏指针
    GameType game_type; // 存储游戏类型

    //ai *NoGoAI;

    int TimerCountNumber;
    int TimerLimit = 30;//后期可在软件内设置

    int clickPosRow,clickPosCol; // 存储即将点击的位置
    bool selectPos = false; // 是否移动到合适的位置，以选中某个交叉点
    bool lose = false;//解决AI重开先后手问题

    // 绘制
    void paintEvent(QPaintEvent * event);

    void initGame();
    void initGameMode(GameType type);//切换开局模式
    void reGame();//实现再来一局

    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void chessOneByPerson();

    void timelimit_exceeded();//超时
    void timer_update();//重新倒计时

private slots:
    void on_pushButton_Surrender_clicked();//认输
    void TimerCount();//一秒一刷新
    void on_pushButton_Cheating_clicked();
};


#endif // MAINWINDOW_H
