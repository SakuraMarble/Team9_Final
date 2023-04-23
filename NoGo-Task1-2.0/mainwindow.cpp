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

    Logs.resize(2);
    documentPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);//Windows用户默认文档保存位置
    subdirectory = "NoGo_Logs";
    dir = QDir(documentPath + "/" + subdirectory);
    if (!dir.exists())
    dir.mkpath(".");

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
    ai newai;
    if(game_type == MAN)
    {
        if(game->playerFlag == true)
        {
            ui->statusbar->setStyleSheet("font-size:23px;color:black;");
            ui->statusbar->showMessage("Black is thinking...");
            ui->label_possible->setText("Black Advantage:"+QString::number(newai.get_possi(game->gameMapVec,game->playerFlag,BOARD_GRAD_SIZE)));
        } else {
            ui->statusbar->setStyleSheet("font-size:23px;color:white;");
            ui->label_UserName->setStyleSheet("color:black;");
            ui->label_UserNameNotion->setStyleSheet("color:black;");
            ui->statusbar->showMessage("White is thinking...");
            ui->label_possible->setText("White Advantage:"+QString::number(newai.get_possi(game->gameMapVec,game->playerFlag,BOARD_GRAD_SIZE)));
        }
    }
    if(game_type == AI)
    {
        if(game->playerFlag == true)
        {
            ui->statusbar->setStyleSheet("font-size:23px;color:black;");
            ui->statusbar->showMessage("Black is thinking...");
            ui->label_possible->setText("Black Advantage:"+QString::number(newai.get_possi(game->gameMapVec,game->playerFlag,BOARD_GRAD_SIZE)));
        } else {
            ui->statusbar->setStyleSheet("font-size:23px;color:white;");
            ui->label_UserName->setStyleSheet("color:black;");
            ui->label_UserNameNotion->setStyleSheet("color:black;");
            ui->statusbar->showMessage("White(AI) is thinking...");
            ui->label_possible->setText("AI Advantage:"+QString::number(newai.get_possi(game->gameMapVec,game->playerFlag,BOARD_GRAD_SIZE)));
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
            if(game->totalSteps>0&&i==lastx&&j==lasty){
                QLinearGradient gradient(MARGIN + BLOCK_SIZE * j - 1.5 * CHESS_RADIUS, MARGIN + BLOCK_SIZE * i - 1.5 * CHESS_RADIUS, MARGIN + BLOCK_SIZE * j , MARGIN + BLOCK_SIZE * i);

                gradient.setColorAt(1, QColor(0, 255, 0));
                gradient.setColorAt(0, QColor(255,0,0));
                painter.setBrush(gradient);
                painter.drawEllipse(MARGIN + BLOCK_SIZE * j - CHESS_RADIUS*1.2,MARGIN + BLOCK_SIZE * i - CHESS_RADIUS*1.2,CHESS_RADIUS * 2.4,CHESS_RADIUS * 2.4);

            }
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
    if (game_type != View)//复现模式下无需倒计时
        timer_init();
    if (game_type == View && logs_empty)
        reGame();
}

void MainWindow::reGame()
{
    //view_lose = false;
    logs_empty = false;
    choosemode();

    initGameMode(game_type);
    if (game_type != View)
        timer_init();
    if (game_type == View && logs_empty)
        reGame();
}

void MainWindow::initGameMode(GameType type)
{
    game->totalSteps=0;
    game->totalTime=0;
    game->gameStatus = PLAYING;
    game->startGame(type);
    update();
    if (game_type == View && !logs_empty)
        QMessageBox::information (this, "Tips", "点击任意落子处复现下一步");
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
        /*
        if (clickPosRow > 0 && clickPosRow < BOARD_GRAD_SIZE &&
            clickPosCol > 0 && clickPosCol < BOARD_GRAD_SIZE &&
            (game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
             game->gameMapVec[clickPosRow][clickPosCol] == 0))
        {

        }*/


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

    if (lose || view_lose) {
        lose = false;//下一局的flag设置
        view_lose = false;
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
    if (game_type == View) {
        if (Logs[game->playerFlag].empty()) {//认输编码'G'不会读入，等效无子
            QString str;
            if (game->playerFlag)
                str = "The white"; //黑色无子白色赢！
            else
                str = "The black"; //白色无子黑色win！
            QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", str + " wins！");
            if (btnValue == QMessageBox::Ok) {
                ask_keeplogs();//询问是否保存对局记录
                view_lose = true;
                //reGame();
                //return;
            }
        }
        else {
            info now_move;
            now_move = Logs[game->playerFlag].front();//顺序复现
            if (Logs[game->playerFlag].size() == 1)
                Logs[game->playerFlag].clear();
            else
                Logs[game->playerFlag].erase(Logs[game->playerFlag].begin());
            /*if (now_move.first == 'G' && !now_move.second) {
                on_pushButton_Surrender_clicked();
                view_lose = true;
                //return;//认输一步
            }*/
            //else {
            clickPosRow = now_move.first - 'A' + 1;
            clickPosCol = now_move.second;

            //}
        }
    }

    // 根据当前存储的坐标下子
    // 只有有效点击才行，并且该处没有子
    if (clickPosRow != -1 && clickPosCol != -1 && game->gameMapVec[clickPosRow][clickPosCol] == -1 && !view_lose)
    {
        game->totalSteps++;
        if(game->playerFlag == true)
            game->totalSteps_black++;
        if(game->playerFlag == false)
            game->totalSteps_white++;
        // 在游戏的数据模型中落子
        if (game_type != View)
            Logs[game->playerFlag].emplace_back(make_pair(clickPosRow - 1 + 'A',clickPosCol));
        lastx=clickPosRow;
        lasty=clickPosCol;
        game->actionByPerson(clickPosRow, clickPosCol);//此处已换手
        // 播放落子音效，待实现；

        if (game->isLose(clickPosRow, clickPosCol) && game->gameStatus == PLAYING)
        {
            //qDebug() << "胜利"；
            game->gameStatus = DEAD;
            if (game_type != View)
                timer->stop();//停止计时
            //QSound::play(":sound/win.wav");
            QString str;
            if (game->gameMapVec[clickPosRow][clickPosCol] == 1)
                str = "The white";//默认白色方是AI，玩家战败
            else if (game->gameMapVec[clickPosRow][clickPosCol] == 0)
                str = "The black";
            lose = true;//用于对局return

        QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", str + " wins!"+" \n Total steps:"+QString::number(game->totalSteps,10)
                                                                         +" \n Total time:"+QString::number(game->totalTime,10)+" s"+" \n Average time of black:"+QString::number(1.0*game->totalTime_black/game->totalSteps_black)
                                                                         +" s"+" \n Average time of white:"+QString::number(1.0*game->totalTime_white/game->totalSteps_white)+" s");
            if (btnValue == QMessageBox::Ok) {
                ask_keeplogs();//询问是否保存对局记录
                reGame();
            }
        }

        //update();
        if (game_type != View)
            timer_update();//重新倒计时
    }
    if (view_lose)
        reGame();
}

void MainWindow::on_pushButton_Surrender_clicked()
{
    game->totalSteps++;
    game->gameStatus = DEAD;
    if (game_type != View)
        timer->stop();//停止计时
    if (game_type != View)
        Logs[game->playerFlag].emplace_back(make_pair('G',0));
    QString str;
    if (game->playerFlag)
        str = "The white"; //黑色认输白色赢！

    else
        str = "The black"; //白色认输黑色win！

    QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", str + " wins!"+" \n Total steps:"+QString::number(game->totalSteps,10)
                                                                     +" \n Total time:"+QString::number(game->totalTime,10)+" s"+" \n Average time of black:"+QString::number(1.0*game->totalTime_black/game->totalSteps_black)
                                                                     +" s"+" \n Average time of white:"+QString::number(1.0*game->totalTime_white/game->totalSteps_white)+" s");
    if (btnValue == QMessageBox::Ok) {
        ask_keeplogs();//询问是否保存对局记录
        if (game_type != View)
            reGame();
    }
}

void MainWindow::timer_init()
{
    timer = new QTimer;
    countlabel = ui->label;
    //countlabel->setGeometry(QRect(280,0,60,25));
    countlabel->setStyleSheet("font-family:\"Lucida Handwriting\";font-size:23px;");
    //countlabel->setAlignment(Qt::AlignHCenter);
    timer->setInterval(1000);//1s刷新一次
    TimerCountNumber = TimerLimit;

    connect(timer,&QTimer::timeout,this,&MainWindow::TimerCount);//关联刷新倒计时
    //if (timer->isActive())
    countlabel->setText("Remaining time:"+QString::number(TimerCountNumber));
    timer->start();
}

void MainWindow::TimerCount()
{
    game->totalTime++;
    if(game->playerFlag == true)
        game->totalTime_black++;
    if(game->playerFlag == false)
        game->totalTime_white++;
    TimerCountNumber--;//1s过去了
    countlabel->setText("Remaining time:"+QString::number(TimerCountNumber));//刷新倒计时
    countlabel->adjustSize();
    //setCentralWidget(centralWidget);
    if(TimerCountNumber <= 5)
    {
        countlabel->setStyleSheet("font-family:\"Lucida Handwriting\";font-size:23px;color:red;");
    }
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
    countlabel->setText("Remaining time:"+QString::number(TimerCountNumber));
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

    QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", str + " wins!"+" \n Total steps:"+QString::number(game->totalSteps,10)
                                                                     +" \n Total time:"+QString::number(game->totalTime,10)+" s"+" \n Average time of black:"+QString::number(1.0*game->totalTime_black/game->totalSteps_black)
                                                                     +" s"+" \n Average time of white:"+QString::number(1.0*game->totalTime_white/game->totalSteps_white)+" s");
    if (btnValue == QMessageBox::Ok) {
        ask_keeplogs();//询问是否保存对局记录
        reGame();
    }
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
        QMessageBox::StandardButton btnValue = QMessageBox::information (this, "NoGo Result", str + " wins!"+" \n Total steps:"+QString::number(game->totalSteps,10)
                                                                         +" \n Total time:"+QString::number(game->totalTime,10)+" s"+" \n Average time of black:"+QString::number(1.0*game->totalTime_black/game->totalSteps_black)
                                                                         +" s"+" \n Average time of white:"+QString::number(1.0*game->totalTime_white/game->totalSteps_white)+" s");
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
        game->BOARD_GRAD_SIZE = 10;
        BOARD_GRAD_SIZE = 10;
    }
    if (game_type == View)
        choose_logs();

    // 设置窗口大小
    setFixedSize(
        MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE,
        MARGIN * 2 + BLOCK_SIZE * BOARD_GRAD_SIZE);
    TimerLimit = dialog->timelimit;
    delete dialog;
}

void MainWindow::ask_keeplogs()
{

    int res = QMessageBox::question(this, tr("Asking"), tr("Whether to keep logs?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);//默认不保存
    if (res == QMessageBox::Yes && game_type != View) {
    
        //用户选择保存记录

        auto now_time = std::chrono::system_clock::now();//获取时间
        auto timestamp = std::chrono::system_clock::to_time_t(now_time);//转换成本地时间
        std::stringstream log_time;
        log_time << std::put_time(std::localtime(&timestamp), "%Y-%m-%d_%H.%M.%S");//规范时间格式 不能有'/' ':'
        QString filename = "Log_" + QString::fromStdString(log_time.str()) + ".txt";
        QString filepath = dir.absoluteFilePath(filename);
        std::ofstream out(filepath.toStdString());

        if (out.is_open()) {
            for (int i = 1;i >= 0;i--) {
                for (const auto& p : Logs[i]) {
                    if (!p.second && p.first == 'G')//认输记录为"G0" 按要求只输出'G'
                        out << p.first << ' ';
                    else
                        out << p.first << p.second << ' ';
                }
                out << std::endl;//代表一方记录输出结束
            }
            out << BOARD_GRAD_SIZE << endl;
            out.close();

            QMessageBox::information(this, tr("Done!"), tr("Your logs have been saved!"));
        }

        else {
            QMessageBox::warning(this, tr("Warning"), tr("Can't create a file"));
        }
    }

    else {
        //不保存
    }

    for (int i = 0;i <= 1;i++) {
        if (!Logs[i].empty())
            Logs[i].clear();
    }
    //清空记录
}

void MainWindow::choose_logs()
{
    QString selectedFilePath = QFileDialog::getOpenFileName(this, "Select Log File", dir.absolutePath(), "Text Files (*.txt)");
    QStringList filter;
    filter << "*.txt";
    QFileInfoList fileList = dir.entryInfoList(filter, QDir::Files);
    if (fileList.isEmpty()) {
        QMessageBox::warning(nullptr, "Oops!", "No log file found");
        logs_empty = true;
        return;
    }
    else {
        if (selectedFilePath.isEmpty()) {
            QMessageBox::warning(nullptr, "Oops!", "No log file selected");
            logs_empty = true;
            return;
        }
        //QString selectedFilePath = QFileDialog::getOpenFileName(this, "Select Log File", dir.absolutePath(), "*.txt");
        qDebug() << selectedFilePath;
        if (!selectedFilePath.isEmpty()) {
            std::ifstream in(selectedFilePath.toStdString());
            if (!in) {
                QMessageBox::warning(this, "Warning", "Failed to open log file.");
            }
            // 读取文件内容
            else {
                std::string line;
                for (int i = 1;i >= 0;i--) {
                    std::getline(in, line);
                    std::stringstream tmp(line);
                    char first;
                    int second;
                    while(tmp >> first >> second)
                        Logs[i].emplace_back(first, second);
                }//第一行为黑棋记录，第二行为白棋记录
                std::getline(in,line);
                std::stringstream tmp(line);
                tmp >> BOARD_GRAD_SIZE;
                game->BOARD_GRAD_SIZE = BOARD_GRAD_SIZE;//第三行为棋盘路数
                in.close();
                std::cout << "Read log file successfully." << std::endl;
                std::cout << "Black player's moves:" << std::endl;
                for (const auto& move : Logs[1]) {
                    std::cout << move.first << move.second << std::endl;
                }
                std::cout << "White player's moves:" << std::endl;
                for (const auto& move : Logs[0]) {
                    std::cout << move.first << move.second << std::endl;
                }
            }
        }
        else logs_empty = true;
    }
}
