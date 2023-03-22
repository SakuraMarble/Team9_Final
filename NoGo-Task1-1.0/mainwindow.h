#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "GameModel.h"
#include <QAbstractButton>
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
<<<<<<< HEAD
    void timer_init();

=======
    void buttonClicked(QAbstractButton *butClicked);
>>>>>>> 484e0405fa88a3102201ad655471fa4da7f358c4
private:
    Ui::MainWindow *ui;

    QTimer *timer;
    QLabel *countlabel;
    //QVBoxLayout *layout;
    //QWidget *centralWidget;
    GameModel *game; // 游戏指针
    GameType game_type; // 存储游戏类型

    int TimerCountNumber;
    int TimerLimit = 30;

    int clickPosRow,clickPosCol; // 存储即将点击的位置
    bool selectPos = false; // 是否移动到合适的位置，以选中某个交叉点


    // 绘制
    void paintEvent(QPaintEvent * event);

    void initGame();
    void initAIGame();

    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void chessOneByPerson();

    void timelimit_exceeded();
    void timer_update();

private slots:
    void on_pushButton_clicked();
    void TimerCount();
};


#endif // MAINWINDOW_H
