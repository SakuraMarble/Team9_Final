#include"nogo_ai.h"
#include<qdebug.h>
#include<iostream>
int ai::findai_fa(int i){
        //并查集
        if(i==ai_fa[i])return i;
        else ai_fa[i]=findai_fa(ai_fa[i]);
        return ai_fa[i];
}
void ai::ai_merge(int sour,int dest){
        //并查集
        ai_fa[findai_fa(sour)]=findai_fa(dest);
    }
bool ai::ai_check(brd &board,int size){
        //检测当前棋盘状态
        for(int i=1;i<10000;i++){ai_fa[i]=i;air[i]=0;}
        for(int i=1;i<size;i++)
            for(int j=1;j<size;j++)
                if(board[i][j]!=ai_empty){
                if(i>0&&board[i][j]==board[i-1][j])
                    ai_merge(i*size+j,i*size-size+j);
                if(j>0&&board[i][j]==board[i][j-1])
                    ai_merge(i*size+j,i*size+j-1);
            }
        for(int i=1;i<size;i++)
            for(int j=1;j<size;j++)
                if(board[i][j]==ai_empty){
                    if(i>=1)air[findai_fa((i-1)*size+j)]++;
                    if(j>=1)air[findai_fa((i)*size+j-1)]++;
                    if(i<size-1)air[findai_fa((i+1)*size+j)]++;
                    if(j<size-1)air[findai_fa((i)*size+j+1)]++;
                    //是否重复无所谓
                }
        for(int i=1;i<size;i++)
            for(int j=1;j<size;j++)
                if(board[i][j]!=ai_empty){
                    if(air[findai_fa(i*size+j)]==0)return false;
                }
        return true;
    }
int ai::ai_calc(int xxx,int yyy,brd &board,int use,int size){
    //玩家use已落子，判断这个子对他的作用
        int val=0;
        int enemy=1-use;
        for(int i=1;i<size;i++)
            for(int j=1;j<size;j++){
                if(board[i][j]==ai_empty){
                    board[i][j]=use;
                    if(ai_check(board,size)){
                        val+=100;
                    }
                    board[i][j]=ai_empty;


                    board[i][j]=enemy;
                    if(ai_check(board,size)){
                        val-=100;

                    }
                    else disbld[xxx][yyy].push_back(i*size+j);
                    board[i][j]=ai_empty;
                }
            }
        return val;
    }
pii ai::thinking(brd &board,int use,int size){
    //程序的接口
    qDebug()<<"ai::thinking";        const int enemy=1-use;
        int worth[size][size];
        int pre_worth[size][size];
        memset(worth,0,sizeof(worth));
        worth[1][1]=50;
        worth[1][size-1]=51;
        worth[size-1][1]=52;
        worth[size-1][size-1]=53;
        for(int i=1;i<size;i++)
            for(int j=1;j<size;j++){
                if(board[i][j]!=ai_empty)worth[i][j]=-1e7;
                else{
                    pre_worth[i][j]=ai_calc(i,j,board,use,size)+ai_calc(i,j,board,enemy,size);
                    if(i<=2||i>=size-2)worth[i][j]+=1;
                    if(j<=2||j>=size-2)worth[i][j]+=1;
                    bool zs=(i>=0&&j-1>=0&&board[i][j-1]==use);
                    bool ys=(i>=0&&j+1<size&&board[i][j+1]==use);
                    bool zx=(i+1<size&&j>=0&&board[i+1][j]==use);
                    bool yx=(i-1>=0&&j<size&&board[i-1][j]==use);
                    int summ=(int)zs+(int)ys+(int)zx+(int)yx;
                    worth[i][j]-=summ*1;
                    zs=(i>=0&&j-1>=0&&board[i][j-1]==enemy);
                    ys=(i>=0&&j+1<size&&board[i][j+1]==enemy);
                    zx=(i+1<size&&j>=0&&board[i+1][j]==enemy);
                    yx=(i-1>=0&&j<size&&board[i-1][j]==enemy);
                    summ=(int)zs+(int)ys+(int)zx+(int)yx;
                    worth[i][j]+=summ*1;
                    board[i][j]=use;
                    if(ai_check(board,size)){
                        worth[i][j]+=ai_calc(i,j,board,use,size);
                    }
                    else worth[i][j]=-1e6;
                    board[i][j]=ai_empty;


                    board[i][j]=enemy;
                    if(ai_check(board,size)){
                        worth[i][j]+=ai_calc(i,j,board,enemy,size);
                    }
                    board[i][j]=ai_empty;
                    worth[i][j]-=pre_worth[i][j];

                }
            }
        int real_worth[size][size];
        for(int i=1;i<size;i++)
            for(int j=1;j<size;j++){
                real_worth[i][j]=worth[i][j];
                for(int t=0;t<disbld[i][j].size();t++)
                    real_worth[i][j]+=max(worth[disbld[i][j][t]/size][disbld[i][j][t]%size]/100*100,0);
            }
        int mn=-1e8;
        int x=1,y=1;
        for(int i=1;i<size;i++)
            for(int j=1;j<size;j++)
                if(real_worth[i][j]>mn){
                    mn=real_worth[i][j];
                    x=i;
                    y=j;
                }
        QDebug deb = qDebug();
        for(int i=1;i<size;i++){
            for(int j=1;j<size;j++)
                deb<<real_worth[i][j]<<" ";deb<<'\n';}deb<<'\n';
            for(int i=1;i<size;i++){
                for(int j=1;j<size;j++)
                    deb<<worth[i][j]<<" ";deb<<'\n';
        }
        return make_pair(x,y);
    }
int ai::get_possi(brd &board,int use,int size){//判断优势
    return ai_calc(1,1,board,use,size)/100;
}
bool ai::ai_try(brd &board,int x,int y,int col,int size){//判断是否可行
    if(board[x][y]!=ai_empty)return false;
    board[x][y]=col;
    bool ret=ai_check(board,size);
    board[x][y]=ai_empty;
    return ret;
}
