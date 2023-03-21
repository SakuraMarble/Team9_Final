#include "countwidget.h"

void CountWidget::timer_init()
{
    timer = new QTimer;
    countlabel = new QLabel;
    timer->setInterval(1000);
    count = 10;
    connect(timer,&QTimer::timeout,this,&CountWidget::TimerCount);
    if (timer->isActive())
        timer->start();
}

void CountWidget::TimerCount()
{
    count--;
    countlabel->setText(QString::number(count));
    if (!count) {
        timer->stop();
        timelimit_exceeded();
    }
}

void CountWidget::timer_update()
{
    timer->stop();
    count = 10;
    if (timer->isActive())
        timer->start();
}

void CountWidget::timelimit_exceeded()
{
    game->gameStatus = DEAD;
    QString str;
    if (game->playerFlag)
        str = "The white"; //黑色TL白色赢！
    else
        str = "The black"; //白色TL黑色win！

    QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", str + " wins！");
    if (btnValue == QMessageBox::Ok)
    {
        game->startGame(game_type);
        game->gameStatus = PLAYING;
    }
    timer_update();
}

