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
#define empty 0
#define black 1
#define white -1
//#endif
#define pii pair<int,int>
class ai{
    static int fa[100];//并查集
    static int air[100];
    static int findfa(int i){
        //并查集
        if(i==fa[i])return i;
        else fa[i]=findfa(i);
        return fa[i];
    }
    static void merge(int sour,int dest){
        //并查集
        fa[findfa(sour)]=findfa(dest);
    }
    static bool check(int board[9][9],int size=9){
        //检测当前棋盘状态
        for(int i=1;i<100;i++){fa[i]=i;air[i]=0;}
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++){
                if(i>0&&board[i][j]==board[i-1][j])
                    merge(i*size+j,i*size-size+j);
                if(j>0&&board[i][j]==board[i][j-1])
                    merge(i*size+j,i*size+j-1);
            }
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                if(board[i][j]==empty){
                    if(i>=1)air[findfa((i-1)*9+j)]++;
                    if(j>=1)air[findfa((i)*9+j-1)]++;
                    if(i<8)air[findfa((i+1)*9+j)]++;
                    if(j<8)air[findfa((i)*9+j+1)]++;
                    //是否重复无所谓
                }
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                if(board[i][j]!=empty){
                    if(air[findfa(i*9+j)]==0)return false;
                }
        return true;
    }
    static int calc(int board[9][9],int use,int size=9){
    //玩家use已落子，判断这个子对他的作用
        int val=0;
        int enemy=-use;
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++){
                if(board[i][j]==empty){
                    board[i][j]=use;
                    if(check(board)){
                        val+=100;
                    }
                    board[i][j]=empty;


                    board[i][j]=enemy;
                    if(check(board)){
                        val-=100;
                    }
                    board[i][j]=empty;
                }
            }
        return val;
    }
public:
    static pii run(int board[9][9],int use,int size=9){
    //程序的接口
        const int enemy=-use;
        int worth[9][9];
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++){
                if(board[i][j]!=empty)worth[i][j]=-1e7;
                else{
                    if(i<=1||i>=7)worth[i][j]+=10;
                    if(j<=1||j>=7)worth[i][j]+=10;
                    if((i==0||i==8)&&(j==0||j==8))worth[i][j]-=10;
                    if((i==1||i==7)&&(j==1||j==7))worth[i][j]-=10;
                    
                    board[i][j]=use;
                    if(check(board)){
                        worth[i][j]=calc(board,use,size);
                    }
                    else worth[i][j]=-1e6;
                    board[i][j]=empty;


                    board[i][j]=enemy;
                    if(check(board)){
                        worth[i][j]+=calc(board,enemy,size);
                    }
                    board[i][j]=empty;


                }
            }
        int mn=-1e8;
        int x=0,y=0;
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                if(worth[i][j]>mn){
                    mn=worth[i][j];
                    x=i;
                    y=j;
                }
        return make_pair(x,y);
    }
};
#endif
