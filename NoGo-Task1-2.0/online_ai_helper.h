/*
本文件作用：实现ai。
调用方式：ai.run(棋盘数组名，目前颜色，棋盘大小)
棋盘大小目前只能设置为9
返回值：pair<int,int>表示ai判断应该下在哪里。
*/
#ifndef OnlineAI
#define OnlineAI 3373
#include<bits/stdc++.h>
#include<QObject>
#include<QRunnable>
using namespace std;
//#ifndef empty
typedef std::vector<int> vect;
typedef vector< vect > brd;
#define ai_empty -1
#define ai_black 1
#define ai_white 0
//#define board gameMapVec
//#define size BOARD_GRAD_SIZE
#define pii pair<int,int>
class Online_Ai_Helper : public QObject,public QRunnable{
    Q_OBJECT
    int ai_fa[10000];//并查集
    int air[10000];
    int findai_fa(int i);
    void ai_merge(int sour,int dest);
    int ai_calc(brd &board,int use,int size);
public:
    bool ai_check(brd &board,int size);
    pii thinking(brd &board,int use,int size);
    int get_possi(brd&board,int use,int size);
    bool ai_try(brd &board,int x,int y,int col,int size);

    explicit Online_Ai_Helper() {};
    ~Online_Ai_Helper();
    void run();
    void send_mes(brd& now_board,int now_use,int now_size);//传入用于计算的对局信息

signals:
    void finished(pii result);

private:
    pii cal_res;
    brd board;
    int use;
    int size;
};
#endif
