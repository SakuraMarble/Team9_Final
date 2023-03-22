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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void timer_init();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    QLabel *countlabel;
    //QVBoxLayout *layout;
    //QWidget *centralWidget;
    QPushButton *agreeBut;
    QPushButton *disagreeBut;

    GameModel *game; // 游戏指针
    GameType game_type; // 存储游戏类型

    int TimerCountNumber;
    int TimerLimit = 30;

    int clickPosRow,clickPosCol; // 存储即将点击的位置
    bool selectPos = false; // 是否移动到合适的位置，以选中某个交叉点
    bool man_lose = false;//解决AI重开先后手问题

    // 绘制
    void paintEvent(QPaintEvent * event);

    void initGame();
    void initGameMode(GameType type);
    void reGame();

    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void chessOneByPerson();

    void timelimit_exceeded();
    void timer_update();

private slots:
    void on_pushButton_clicked();
    void TimerCount();
    void buttonClicked(QAbstractButton *butClicked);
};


#endif // MAINWINDOW_H
