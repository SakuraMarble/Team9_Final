#include"nogo_ai.h"
int ai::findai_fa(int i){
        //并查集
        if(i==ai_fa[i])return i;
        else ai_fa[i]=findai_fa(i);
        return ai_fa[i];
}
void ai::ai_merge(int sour,int dest){
        //并查集
        ai_fa[findai_fa(sour)]=findai_fa(dest);
    }
bool ai::ai_check(brd board,int size){
        //检测当前棋盘状态
        for(int i=1;i<100;i++){ai_fa[i]=i;air[i]=0;}
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++){
                if(i>0&&board[i][j]==board[i-1][j])
                    ai_merge(i*size+j,i*size-size+j);
                if(j>0&&board[i][j]==board[i][j-1])
                    ai_merge(i*size+j,i*size+j-1);
            }
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                if(board[i][j]==ai_empty){
                    if(i>=1)air[findai_fa((i-1)*size+j)]++;
                    if(j>=1)air[findai_fa((i)*size+j-1)]++;
                    if(i<size-1)air[findai_fa((i+1)*size+j)]++;
                    if(j<size-1)air[findai_fa((i)*size+j+1)]++;
                    //是否重复无所谓
                }
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++)
                if(board[i][j]!=ai_empty){
                    if(air[findai_fa(i*size+j)]==0)return false;
                }
        return true;
    }
int ai::ai_calc(brd board,int use,int size){
    //玩家use已落子，判断这个子对他的作用
        int val=0;
        int enemy=1-use;
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++){
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
                    board[i][j]=ai_empty;
                }
            }
        return val;
    }
pii ai::run(brd board,int use,int size){
    //程序的接口
        const int enemy=1-use;
        int worth[size][size];
        for(int i=0;i<size;i++)
            for(int j=0;j<size;j++){
                if(board[i][j]!=ai_empty)worth[i][j]=-1e7;
                else{
                    if(i<=1||i>=size-2)worth[i][j]+=10;
                    if(j<=1||j>=size-2)worth[i][j]+=10;
                    if((i==0||i==size-1)&&(j==0||j==size-1))worth[i][j]-=10;
                    if((i==1||i==size-2)&&(j==1||j==size-2))worth[i][j]-=10;

                    board[i][j]=use;
                    if(ai_check(board,size)){
                        worth[i][j]=ai_calc(board,use,size);
                    }
                    else worth[i][j]=-1e6;
                    board[i][j]=ai_empty;


                    board[i][j]=enemy;
                    if(ai_check(board,size)){
                        worth[i][j]+=ai_calc(board,enemy,size);
                    }
                    board[i][j]=ai_empty;


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
