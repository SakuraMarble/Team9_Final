#ifndef GAMEMODEL_H
#define GAMEMODEL_H

// --- NoGo游戏模型类 ---//
#include<vector>
#define group_size 1515

//游戏类型，双人还是AI（目前固定让AI下黑子）
enum GameType
{
    MAN,
    AI
};

//游戏状态
enum GameStatus
{
    PLAYING,
    WIN,
    DEAD
};

//棋盘尺寸
const int BOARD_GRAD_SIZE = 10;

const int MARGIN = 30; // 棋盘边缘空隙
const int CHESS_RADIUS = 15; // 棋子半径
const int MARK_SIZE = 6; // 落子标记边长
const int BLOCK_SIZE = 40; // 格子大小
const int POS_OFFSET = BLOCK_SIZE * 0.4; // 20 鼠标点击的模糊距离上限

const int AI_THINK_TIME = 700; // AI下棋思考时间

class GameModel{
public:
    GameModel(){};
public:
    int group[2][group_size];
    int rank[2][group_size];
    int direction[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    //存储当前游戏棋盘和棋子的情况，空白为-1，黑子1，白子0
    std::vector<std::vector<int>> gameMapVec;

    //存储各个点位的评分情况，作为AI下棋的依据
    std::vector<std::vector<int>> scoreMapVec;

    //标记下棋方，true:黑棋方 false：AI白棋方
    bool playerFlag;

    GameType gameType; //游戏模式：PVPorPVE

    GameStatus gameStatus; //游戏状态

    void startGame(GameType type); // 确定游戏模式，开始游戏

    void actionByPerson(int row, int col); // 人执行下棋
    void updateGameMap(int row, int col);  // 更新第几行第几列的数据

    bool isLose(int row, int col);
    bool if_out(int row,int col);
    bool if_air(int group,int player);
    bool eat(int row,int col,int player);

    void calculateScore(); // 为AI计算评分
    void merge(int i,int j,int player);
    int find(int x,int player);

    int merge_group(int row,int col);

    void actionByAI(int &clickRow, int &clickCol);// 机器执行下棋
};

#endif // GAMEMODEL_H
