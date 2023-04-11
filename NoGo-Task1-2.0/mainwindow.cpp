#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QMessageBox>
#include "dialogchoosemode.h"
MainWindow::MainWindow(QWidget *parent,QString username)
    : QMainWindow(parent),UserName(username), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setMouseTracking(true);
    // 设置窗口大小
    setFixedSize(
        MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,
        MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE);
    ui->statusbar->addPermanentWidget(ui->label_UserNameNotion);
    if(UserName != "team9")
    {
        ui->label_UserName->setText(UserName);
    } else {
    ui->label_UserName->setStyleSheet("color:red;");
    ui->label_UserName->setText(UserName+"(You are the VIP)");
    }
    ui->statusbar->addPermanentWidget(ui->label_UserName);
    initGame();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//实现paintEvent方法
void MainWindow::paintEvent(QPaintEvent * event)
{
    QPixmap pixmap;
    pixmap.load(":/img/img/Wood.jpg");
    pixmap = pixmap.scaled(MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE);

    QPainter paint(this);
    paint.drawPixmap(0, 0, pixmap);
    QWidget::paintEvent(event);
    if(game_type == MAN)
    {
        if(game->playerFlag == true)
        {
            ui->statusbar->showMessage("Black is thinking...");
        } else {
        ui->statusbar->showMessage("White is thinking...");
        }
    }
    if(game_type == AI)
    {
        if(game->playerFlag == true)
        {
            ui->statusbar->showMessage("Black is thinking...");
        } else {
        ui->statusbar->showMessage("White(AI) is thinking...");
        }
    }
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
    // 设置画笔颜色、宽度
    painter.setPen(QPen(Qt::transparent, 2));
    for (int i = 0; i < BOARD_GRAD_SIZE; i++)
        for (int j = 0; j < BOARD_GRAD_SIZE; j++)
        {
            if (game->gameMapVec[i][j] == 1)
            {
                QLinearGradient gradient(MARGIN + BLOCK_SIZE * j - 1.5 * CHESS_RADIUS, MARGIN + BLOCK_SIZE * i - 1.5 * CHESS_RADIUS, MARGIN + BLOCK_SIZE * j , MARGIN + BLOCK_SIZE * i);
                gradient.setColorAt(0, QColor(255,255,255));
                gradient.setColorAt(1, QColor(0, 0, 0));

                painter.setBrush(gradient);
                painter.drawEllipse(MARGIN + BLOCK_SIZE * j - CHESS_RADIUS,MARGIN + BLOCK_SIZE * i - CHESS_RADIUS,CHESS_RADIUS * 2,CHESS_RADIUS * 2);
            }
            else if (game->gameMapVec[i][j] == 0)
            {
                QLinearGradient gradient(MARGIN + BLOCK_SIZE * j, MARGIN + BLOCK_SIZE * i, MARGIN + BLOCK_SIZE * j + CHESS_RADIUS, MARGIN + BLOCK_SIZE * i + CHESS_RADIUS);
                gradient.setColorAt(0, QColor(255,255,255));
                gradient.setColorAt(1, QColor(173,216,230));

                painter.setBrush(gradient);
                painter.drawEllipse(MARGIN + BLOCK_SIZE * j - CHESS_RADIUS ,MARGIN + BLOCK_SIZE * i - CHESS_RADIUS ,CHESS_RADIUS * 2,CHESS_RADIUS * 2);
            }
        }
}

void MainWindow::initGame()
{
    // 初始化游戏模型
    game = new GameModel;
    //NoGoAI = new ai;
    //创建消息框
    choosemode();
    initGameMode(game_type);
    timer_init();
}

void MainWindow::reGame()
{
    Black_Log.clear();
    White_Log.clear();
    choosemode();
    initGameMode(game_type);
    timer_update();
}

void MainWindow::initGameMode(GameType type)
{
    game->gameStatus = PLAYING;
    game->startGame(type);
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

        // 判断输赢,请移步mouseReleaseEvent
        if (clickPosRow > 0 && clickPosRow < BOARD_GRAD_SIZE &&
            clickPosCol > 0 && clickPosCol < BOARD_GRAD_SIZE &&
            (game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
             game->gameMapVec[clickPosRow][clickPosCol] == 0))
        {

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

    // 由人持黑子先来下棋
    chessOneByPerson();
    repaint();//立即调用paintEvent进行重绘
    //update();
    //paintEvent(NULL);
    if (lose) {
        lose = false;//下一局的flag设置
        return;//玩家战败，AI无需再下棋
    }
    if (game_type == AI) { //人机模式
        ai newai;
        pii ret=newai.run(game->gameMapVec,game->playerFlag,BOARD_GRAD_SIZE);//向AI传入对局信息并获得AI下棋位置
        clickPosRow=ret.first; clickPosCol=ret.second;

        chessOneByPerson();//其实是ByAI

        //重新绘制
        update();//返回主事件循环时重绘，效率更高但不会立即调用paintEvent

    }
    lose = false;//下一局的flag设置
}

void MainWindow::chessOneByPerson()
{
    // 根据当前存储的坐标下子
    // 只有有效点击才行，并且该处没有子
    if (clickPosRow != -1 && clickPosCol != -1 && game->gameMapVec[clickPosRow][clickPosCol] == -1)
    {
        // 在游戏的数据模型中落子
        if (game->playerFlag)
            Black_Log.push_back(make_pair(clickPosRow - 1 + 'A',clickPosCol));
        else
            White_Log.push_back(make_pair(clickPosRow - 1 + 'A',clickPosCol)); //记录对局信息
        game->actionByPerson(clickPosRow, clickPosCol);//此处已换手
        // 播放落子音效，待实现；
        if (game->isLose(clickPosRow, clickPosCol) && game->gameStatus == PLAYING)
        {
            //qDebug() << "胜利"；
            game->gameStatus = DEAD;
            timer->stop();//停止计时
            //QSound::play(":sound/win.wav");
            QString str;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                str = "The white";//默认白色方是AI，玩家战败
            else if (game->gameMapVec[clickPosRow][clickPosCol] == 0)
                str = "The black";
            lose = true;//用于对局return

            QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", str + " wins！");
            if (btnValue == QMessageBox::Ok)
                reGame();
        }

        //update();
        timer_update();//重新倒计时
    }
}

void MainWindow::on_pushButton_Surrender_clicked()
{
    game->gameStatus = DEAD;
    timer->stop();//停止计时
    QString str;

    if (game->playerFlag) {
        str = "The white"; //黑色认输白色赢！
        Black_Log.push_back(make_pair('G',0));
    }

    else {
        str = "The black"; //白色认输黑色win！
        White_Log.push_back(make_pair('G',0));//记录认输
    }

    QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", str + " wins！");
    if (btnValue == QMessageBox::Ok)
        reGame();
}

void MainWindow::timer_init()
{
    timer = new QTimer;
    countlabel = ui->label;
    countlabel->setAlignment(Qt::AlignHCenter);

    timer->setInterval(1000);//1s刷新一次
    TimerCountNumber = TimerLimit;

    connect(timer,&QTimer::timeout,this,&MainWindow::TimerCount);//关联刷新倒计时
    //if (timer->isActive())
    countlabel->setText(QString::number(TimerCountNumber));
    timer->start();
}

void MainWindow::TimerCount()
{
    TimerCountNumber--;//1s过去了
    countlabel->setText(QString::number(TimerCountNumber));//刷新倒计时
    //setCentralWidget(centralWidget);
    if (!TimerCountNumber) {
        timer->stop();
        timelimit_exceeded();//超时
    }
}

void MainWindow::timer_update()
{
    timer->stop();
    TimerCountNumber = TimerLimit;
    //if (timer->isActive())
    countlabel->setText(QString::number(TimerCountNumber));
    timer->start();
}

void MainWindow::timelimit_exceeded()
{
    game->gameStatus = DEAD;
    timer->stop();
    QString str;
    if (game->playerFlag)
        str = "The white"; //黑色TL白色赢！
    else
        str = "The black"; //白色TL黑色win！

    QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", "You have exceeded the time limit," + str + " wins！");
    if (btnValue == QMessageBox::Ok)
        reGame();
}

/*void MainWindow::buttonClicked(QAbstractButton *butClicked){//选择是否为对阵AI模式
    if(butClicked == (QAbstractButton*)agreeBut) {
        game_type = AI;
        initGameMode(AI);
    }
    else {
        game_type = MAN;
        initGameMode(MAN);
    }
}*/


void MainWindow::on_pushButton_Cheating_clicked()
{
    if(ui->label_UserName->text() == "team9(You are the VIP)"&& game_type == AI)
    {
        game->gameStatus = DEAD;
        timer->stop();//停止计时
        QString str = "The black";
        lose = true;//用于对局return
        QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", str + " wins！");
        if (btnValue == QMessageBox::Ok)
            reGame();
    }else{
        QMessageBox::warning(this,"Sorry","You're not the VIP or the game type is not PVE,so you can't do this.");
    }
}

void MainWindow::choosemode()
{
    DialogChooseMode *dialog = new DialogChooseMode;
    dialog->exec();
    game_type = dialog->game_typeForAll;

    if (game_type == MAN) {
        game->BOARD_GRAD_SIZE = dialog->pvp_boardsize > 16 ? 16 : dialog->pvp_boardsize;
        if (game->BOARD_GRAD_SIZE < 4)
            game->BOARD_GRAD_SIZE = 4;
        BOARD_GRAD_SIZE = game->BOARD_GRAD_SIZE;
    }
    else {
        game->BOARD_GRAD_SIZE = 16;
        BOARD_GRAD_SIZE = 16;
    }
    // 设置窗口大小
    setFixedSize(
        MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,
        MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE);
    TimerLimit = dialog->timelimit;
    delete dialog;
}
