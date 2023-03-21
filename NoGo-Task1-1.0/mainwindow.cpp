#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <math.h>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setMouseTracking(true);
    // 设置窗口大小
    setFixedSize(
        MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,
        MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE);
    initGame();

}

MainWindow::~MainWindow()
{
    delete ui;
    if (timer) {
        if (timer->isActive())
            timer->stop();
        delete timer;
        timer = nullptr;
    }
    delete label;
    label = nullptr;
}

//实现paintEvent方法
void MainWindow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    // 绘制棋盘
    painter.setRenderHint(QPainter::Antialiasing,true); // 抗锯齿

    for (int i = 0; i < BOARD_GRAD_SIZE + 1; i++)
    {
        // 从左到右，第（i+1）条竖线
        painter.drawLine(MARGIN + BLOCK_SIZE * i, MARGIN,
                         MARGIN + BLOCK_SIZE * i,size().height()-MARGIN);
        // 从上到下，第（i+1）条横线
        painter.drawLine(MARGIN,MARGIN+BLOCK_SIZE * i,
                         size().width()-MARGIN,MARGIN+BLOCK_SIZE * i);

    }

    // 绘制选中点
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    // 绘制落子标记（防止鼠标出框越界）
    if (clickPosRow > 0 && clickPosRow < BOARD_GRAD_SIZE &&
        clickPosCol > 0 && clickPosRow < BOARD_GRAD_SIZE &&
        game->gameMapVec[clickPosRow][clickPosCol] == -1)
    {
        if (game->playerFlag)
            brush.setColor(Qt::black);
        else
            brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawRect(MARGIN + BLOCK_SIZE * clickPosCol - MARK_SIZE / 2, MARGIN + BLOCK_SIZE * clickPosRow - MARK_SIZE / 2,MARK_SIZE,MARK_SIZE);
    }

    // 绘制棋子
    for (int i = 0; i < BOARD_GRAD_SIZE; i++)
        for (int j = 0; j < BOARD_GRAD_SIZE; j++)
        {
            if (game->gameMapVec[i][j] == 1)
            {
                //brush.setColor(Qt::white);
                brush.setColor(Qt::black);

                painter.setBrush(brush);
                painter.drawEllipse(MARGIN + BLOCK_SIZE * j - CHESS_RADIUS,MARGIN + BLOCK_SIZE * i - CHESS_RADIUS,CHESS_RADIUS * 2,CHESS_RADIUS * 2);
            }
            else if (game->gameMapVec[i][j] == 0)
            {
                brush.setColor(Qt::white);

                painter.setBrush(brush);
                painter.drawEllipse(MARGIN + BLOCK_SIZE * j - CHESS_RADIUS,MARGIN + BLOCK_SIZE * i - CHESS_RADIUS,CHESS_RADIUS * 2,CHESS_RADIUS * 2);
            }
        }
}

void MainWindow::initGame()
{
    // 初始化游戏模型
    game = new GameModel;
    timer = new QTimer;
    label = new QLabel;
    timer->setInterval(1000);
    TimerLimit = 10;
    TimerCountNumber = TimerLimit;
    connect(timer,&QTimer::timeout,this,&MainWindow::TimerCount);
    if (timer->isActive())
        timer->start();
    initAIGame();
}

void MainWindow::TimerCount()
{
    TimerCountNumber--;
    ui->label->setText(QString::number(TimerCountNumber));
    if (!TimerCountNumber) {
        timer->stop();
        timelimit_exceeded();
    }
}

void MainWindow::timer_update()
{
    TimerCountNumber = TimerLimit;
    timer->stop();
    if (timer->isActive())
        timer->start();
}

void MainWindow::initAIGame()
{
    game_type = AI;
    game->gameStatus = PLAYING;

    game->startGame(game_type);
    update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    // 通过鼠标的hover确定落子的标记
    int x = event->position().x();
    int y = event->position().y();

    //棋盘n边缘不能落子
    if (x>=MARGIN + BLOCK_SIZE / 2 &&
            x < size().width() - MARGIN - BLOCK_SIZE / 2 &&
            y >= MARGIN + BLOCK_SIZE / 2 &&
            y < size().height() - MARGIN - BLOCK_SIZE / 2)
    {
        //获取最近的左上角的点
        //add by rock
        int col = (x - MARGIN) / BLOCK_SIZE;
        int row = (y - MARGIN) / BLOCK_SIZE;
        //int col = x / kBlockSize;
        //int row = y / kBlockSize;

        int leftTopPosX = MARGIN + BLOCK_SIZE * col;
        int leftTopPosY = MARGIN + BLOCK_SIZE * row;

        //根据距离算出合适的点击位置，一共四个点，根据半径距离选最近的格点
        clickPosRow = -1; // 初始化
        clickPosCol = -1;
        int len = 0; // 计算后取整

        selectPos = false;

        //确定一个误差在范围内的点，且只能确认出一个来
        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < POS_OFFSET)
        {
            clickPosRow = row;
            clickPosCol = col;

            if (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                selectPos = true;
        }

        len = sqrt((x - leftTopPosX - BLOCK_SIZE) * (x - leftTopPosX - BLOCK_SIZE) + (y - leftTopPosY) * (y - leftTopPosY));
        if (len < POS_OFFSET)
        {
            clickPosRow = row;
            clickPosCol = col + 1;

            if (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                selectPos = true;
        }

        len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - BLOCK_SIZE) * (y - leftTopPosY - BLOCK_SIZE));
        if (len < POS_OFFSET)
        {
            clickPosRow = row + 1;
            clickPosCol = col;

            if (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                selectPos = true;
        }

        len = sqrt((x - leftTopPosX - BLOCK_SIZE) * (x - leftTopPosX - BLOCK_SIZE) + (y - leftTopPosY - BLOCK_SIZE) * (y - leftTopPosY - BLOCK_SIZE));
        if (len < POS_OFFSET)
        {
            clickPosRow = row + 1;
            clickPosCol = col + 1;

            if (game->gameMapVec[clickPosRow][clickPosCol] == -1)
                selectPos = true;
        }

        // 判断输赢
        if (clickPosRow > 0 && clickPosRow < BOARD_GRAD_SIZE &&
            clickPosCol > 0 && clickPosCol < BOARD_GRAD_SIZE &&
            (game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
             game->gameMapVec[clickPosRow][clickPosCol] == 0))
        {
            if (game->isLose(clickPosRow, clickPosCol) && game->gameStatus == PLAYING)
            {
                //qDebug() << "胜利"；
                game->gameStatus = DEAD;
                //QSound::play(":sound/win.wav");
                QString str;
                if (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                    str = "The white";
                else if (game->gameMapVec[clickPosRow][clickPosCol] == 0)
                    str = "The black"; //对方胜利

                QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", str + " wins！");
                if (btnValue == QMessageBox::Ok)
                {
                    game->startGame(game_type);
                    game->gameStatus = PLAYING;
                }
                timer_update();
            }
        }


    }

    // 存了坐标之后也要重新绘制
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent * event)
{
    if (selectPos == false) {
        return;
    } else {
        // 在落子之前，把落子标志再设置为false
        selectPos = false;
    }

    // 由人来下棋
    chessOneByPerson();

    if (game_type == AI) { //人机模式
        // AI 下棋
    }
}

void MainWindow::chessOneByPerson()
{
    // 根据当前存储的坐标下子
    // 只有有效点击才行，并且该处没有子
    if (clickPosRow != -1 && clickPosCol != -1 && game->gameMapVec[clickPosRow][clickPosCol] == -1)
    {
        // 在游戏的数据模型中落子
        game->actionByPerson(clickPosRow, clickPosCol);
        // 播放落子音效，待实现；

        // 重新绘制
        update();
        timer_update();
    }
}

void MainWindow::on_pushButton_clicked()
{
    game->gameStatus = DEAD;
    QString str;
    if (game->playerFlag)
        str = "The white"; //黑色认输白色赢！
    else
        str = "The black"; //白色认输黑色win！

    QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", str + " wins！");
    if (btnValue == QMessageBox::Ok)
    {
        game->startGame(game_type);
        game->gameStatus = PLAYING;
    }
    timer_update();
}

void MainWindow::timelimit_exceeded()
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














