#include"online_ai_helper.h"
#include<qdebug.h>
#include<QThread>
Online_Ai_Helper::~Online_Ai_Helper() {
    //qDebug() << "Deconstructor\n";
}

void Online_Ai_Helper::run() {
    QThread::msleep(300);
    cal_res = this->thinking(board, use, size);
    // 发送结果
    emit finished(cal_res);
    //qDebug() << "emit res\n";
    //deleteLater(); // 延迟删除被该对象占用的内存
}

void Online_Ai_Helper::send_mes(brd& now_board,int now_use,int now_size) {
    board = now_board;
    use = now_use;
    size = now_size;
}
