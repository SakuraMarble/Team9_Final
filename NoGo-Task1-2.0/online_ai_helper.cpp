#include"online_ai_helper.h"
#include<qdebug.h>

Online_Ai_Helper::~Online_Ai_Helper() {
    qDebug() << "Deconstructor\n";
}

int Online_Ai_Helper::findai_fa(int i){
    //并查集
    if(i==ai_fa[i])return i;
    else ai_fa[i]=findai_fa(ai_fa[i]);
    return ai_fa[i];
}
void Online_Ai_Helper::ai_merge(int sour,int dest){
    //并查集
    ai_fa[findai_fa(sour)]=findai_fa(dest);
}
bool Online_Ai_Helper::ai_check(brd &board,int size){
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
int Online_Ai_Helper::ai_calc(brd &board,int use,int size){
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
                board[i][j]=ai_empty;
            }
        }
    return val;
}
pii Online_Ai_Helper::thinking(brd &board,int use,int size){
    //程序的接口
    const int enemy=1-use;
    int worth[size][size];
    for(int i=1;i<size;i++)
        for(int j=1;j<size;j++){
            if(board[i][j]!=ai_empty)worth[i][j]=-1e7;
            else{
                if(i<=2||i>=size-2)worth[i][j]+=rand()%10;
                if(j<=2||j>=size-2)worth[i][j]+=rand()%10;
                bool zs=(i-1>=0&&j-1>=0&&board[i-1][j-1]==use);
                bool ys=(i-1>=0&&j+1<size&&board[i-1][j+1]==use);
                bool zx=(i+1<size&&j-1>=0&&board[i+1][j-1]==use);
                bool yx=(i+1<size&&j+1<size&&board[i+1][j+1]==use);
                int summ=(int)zs+(int)ys+(int)zx+(int)yx;
                worth[i][j]+=summ*20;
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
    int x=1,y=1;
    for(int i=1;i<size;i++)
        for(int j=1;j<size;j++)
            if(worth[i][j]>mn){
                mn=worth[i][j];
                x=i;
                y=j;
            }
    return make_pair(x,y);
}
int Online_Ai_Helper::get_possi(brd &board,int use,int size){//判断优势
    return ai_calc(board,use,size)/100;
}
bool Online_Ai_Helper::ai_try(brd &board,int x,int y,int col,int size){//判断是否可行
    if(board[x][y]!=ai_empty)return false;
    board[x][y]=col;
    bool ret=ai_check(board,size);
    board[x][y]=ai_empty;
    return ret;
}

void Online_Ai_Helper::run() {
    cal_res = this->thinking(board, use, size);
    // 发送结果
    emit finished(cal_res);
    qDebug() << "emit res\n";
    //deleteLater(); // 延迟删除被该对象占用的内存
}

void Online_Ai_Helper::send_mes(brd& now_board,int now_use,int now_size) {
    board = now_board;
    use = now_use;
    size = now_size;
}
