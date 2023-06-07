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
bool ai::ai_check(brd &board,int size){//时间复杂度：1000
        //检测当前棋盘状态
        for(int i=1;i<=size*size;i++){ai_fa[i]=i;air[i]=0;}
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
int ai::ai_calc(brd &board,int use,int size){//时间复杂度：10^5
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
                    //else {/*cout << xxx << yyy << endl;*/disbld[xxx][yyy].emplace_back(i*size+j);}
                    board[i][j]=ai_empty;
                }
            }
        return val;
    }
pii ai::thinking(brd &board,int use,int size){
    //程序的接口
    qDebug()<<"ai::thinking";        const int enemy=1-use;
        int worth[size][size];
        //int pre_worth;
        memset(worth,0,sizeof(worth));
        worth[1][1]=50;
        worth[1][size-1]=51;
        worth[size-1][1]=52;
        worth[size-1][size-1]=53;
        int abl=0;
        for(int i=1;i<size;i++)
            for(int j=1;j<size;j++){
                if(board[i][j]==ai_empty){
                    board[i][j]=use;
                    if(ai_check(board,size)){
                        abl+=1;
                    }
                    board[i][j]=ai_empty;}}
        //pre_worth=ai_calc(0,0,board,use,size)+ai_calc(0,0,board,enemy,size);
        for(int i=1;i<size;i++)
            for(int j=1;j<size;j++){
                bool flgemp=false;
                if(worth[i][j]==0){flgemp=true;
                    for(int ii=i-1;ii<=i+1&&ii<size;ii++)
                        for(int jj=j-1;jj<=j+1&&jj<size;jj++)
                            if(board[ii][jj]!=ai_empty)flgemp=false;

                }
                if(flgemp==true)worth[i][j]=-1000;else{
                if(board[i][j]!=ai_empty)worth[i][j]=-1e7;
                else{
                    bool zs=(i-1>=0&&j-1>=0&&board[i-1][j-1]==use);
                    bool ys=(i-1>=0&&j+1<size&&board[i-1][j+1]==use);
                    bool zx=(i+1<size&&j-1>=0&&board[i+1][j-1]==use);
                    bool yx=(i+1<size&&j+1<size&&board[i+1][j+1]==use);
                    int summ=(int)zs+(int)ys+(int)zx+(int)yx;
                    worth[i][j]-=summ*5;
                    zs=(i>=0&&j-1>=0&&board[i][j-1]==enemy);
                    ys=(i<size&&j+1<size&&board[i][j+1]==enemy);
                    zx=(i+1<size&&j>=0&&board[i+1][j]==enemy);
                    yx=(i-1>=0&&j<size&&board[i-1][j]==enemy);
                    summ=(int)zs+(int)ys+(int)zx+(int)yx;
                    worth[i][j]+=summ*6;
                    board[i][j]=use;
                    if(ai_check(board,size)){
                        int min_enemy=1e8;
                        for(int ii=1;ii<size;ii++)
                            for(int jj=1;jj<size;jj++)if(board[ii][jj]==ai_empty){
                                board[ii][jj]=enemy;
                                if(ai_check(board,size))
                                    min_enemy=min(min_enemy,ai_calc(board,use,size));
                                board[ii][jj]=ai_empty;
                            }
                        worth[i][j]+=min_enemy;
                    }
                    else worth[i][j]=-1e6;
                    board[i][j]=ai_empty;


                    //board[i][j]=enemy;
                    //if(ai_check(board,size)){
                    //    worth[i][j]+=ai_calc(i,j,board,enemy,size);
                    //}
                    //board[i][j]=ai_empty;

                    //worth[i][j]-=pre_worth;

                }}
            }
        //int real_worth[size][size];
        //for(int i=1;i<size;i++)
        //    for(int j=1;j<size;j++){
         //       real_worth[i][j]=worth[i][j];
                //for(int t=0;t<disbld[i][j].size();t++)
                 //   real_worth[i][j]+=max(worth[disbld[i][j][t]/size][disbld[i][j][t]%size]/100*100,0);
        //    }
        int mn=-1e8;
        int x=1,y=1;
        for(int i=1;i<size;i++)
            for(int j=1;j<size;j++)
                if(worth[i][j]>mn){
                    mn=worth[i][j];
                    x=i;
                    y=j;
                }
        QDebug deb = qDebug();deb<<'\n';
        for(int i=1;i<size;i++){
            for(int j=1;j<size;j++)
                deb<<worth[i][j]<<" ";deb<<'\n';}


        return make_pair(x,y);
    }
int ai::get_possi(brd &board,int use,int size){//判断优势
    return ai_calc(board,use,size)/100;
}
bool ai::ai_try(brd &board,int x,int y,int col,int size){//判断是否可行
    if(board[x][y]!=ai_empty)return false;
    board[x][y]=col;
    bool ret=ai_check(board,size);
    board[x][y]=ai_empty;
    return ret;
}
