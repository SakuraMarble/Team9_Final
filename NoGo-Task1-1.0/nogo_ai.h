/*
本文件作用：实现ai。
调用方式：ai.run(棋盘数组名，目前颜色，棋盘大小)
棋盘大小目前只能设置为9
返回值：pair<int,int>表示ai判断应该下在哪里。
*/
#ifndef nogoAI
#define nogoAI 3373
#include<bits/stdc++.h>
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
class ai{
    int ai_fa[100];//并查集
    int air[100];
    int findai_fa(int i);
    void ai_merge(int sour,int dest);
    bool ai_check(brd board,int size);
    int ai_calc(brd board,int use,int size);
public:
    pii run(brd board,int use,int size);
};
#endif
