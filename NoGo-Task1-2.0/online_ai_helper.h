/*
本文件作用：实现ai。
调用方式：ai.run(棋盘数组名，目前颜色，棋盘大小)
棋盘大小目前只能设置为9
返回值：pair<int,int>表示ai判断应该下在哪里。
*/
#ifndef OnlineAI
#define OnlineAI 3373
#include<nogo_ai.h>
#include<QObject>
#include<QRunnable>
using namespace std;
class Online_Ai_Helper : public QObject,public QRunnable,public ai{
    Q_OBJECT
public:
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
