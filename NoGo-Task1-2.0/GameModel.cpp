#include "GameModel.h"
#define point_index(row,col) (100 * row + col)
#include "nogo_ai.h"
void GameModel::startGame(GameType type)
{
    gameType = type; // 前面的gameType是GameModel类中的成员变量

    // 初始棋盘
    gameMapVec.clear();
    // 先将一行的-1 push_back进入一个容器中，再将这个lineBoard容器push_back进容器的容器gameMapVec中
    for (int i = 0; i < BOARD_GRAD_SIZE; i++)
    {
        std::vector<int> lineBoard;
        for (int j = 0; j< BOARD_GRAD_SIZE; j++)
            lineBoard.push_back(-1);
        gameMapVec.push_back(lineBoard);
    }

    for (int i = 0;i < 2;i++) {
        for (int j = 0;j < group_size;j++) {
            group[i][j] = j;
            rank[i][j] = 1;
        }
    }

    // 如果是AI模式，还需要初始化评分数组
    if(type == AI)
    {
        scoreMapVec.clear();
        for (int i = 0; i < BOARD_GRAD_SIZE; i++)
        {
            std::vector<int> lineScores;
            for (int j = 0; j < BOARD_GRAD_SIZE; j++)
                lineScores.push_back(0);
            scoreMapVec.push_back(lineScores);
        }
    }

    //轮到黑方下棋为 true，白方为 false
    playerFlag = true;
}

void GameModel::actionByPerson(int row, int col)
{
    updateGameMap(row, col);
}

void GameModel::updateGameMap(int row, int col)
{
    if (playerFlag)
        gameMapVec[row][col] = 1;
    else
        gameMapVec[row][col] = 0;


    // 换手
    playerFlag = !playerFlag;
}

bool GameModel::isLose(int row, int col)//merge_group并查集算法已统一边界标准，人人对战无需多次declare newai
{
    //ai newai;
    //return !newai.ai_check(gameMapVec,BOARD_GRAD_SIZE);
    if (eat(row,col,gameMapVec[row][col]))
        return true; //吃对方判负
    int group = merge_group(row,col);
    if (!if_air(group,gameMapVec[row][col]))
        return true; //紫砂判负
    return false;
}

bool GameModel::if_out(int row,int col)
{
    return (row <= 0 || row >= BOARD_GRAD_SIZE || col <= 0 || col >= BOARD_GRAD_SIZE) ? true : false;
}

int GameModel::merge_group(int row,int col)
{
    int point = point_index(row,col),new_row,new_col,new_point;
    for (int i = 0;i < 4;i++) {
        new_row = row + direction[i][0];
        new_col = col + direction[i][1];
        if (if_out(new_row,new_col))
            continue;
        new_point = point_index(new_row,new_col);
        if (gameMapVec[new_row][new_col] == gameMapVec[row][col])//四周有同色棋子
            merge(point,new_point,gameMapVec[row][col]);
    }

    return find(point,gameMapVec[row][col]);
}

int GameModel::find(int x,int player)
{
    return (x == group[player][x]) ? x : (group[player][x] = find(group[player][x],player));
}

void GameModel::merge(int i,int j,int player)
{
    int x = find(i,player),y = find(j,player);
    if (rank[player][x] <= rank[player][y])
        group[player][x] = y;
    else
        group[player][y] = x;
    if (rank[player][x] == rank[player][y])
        rank[player][y]++;
}

bool GameModel::eat(int row,int col,int player)
{
    int i,new_row,new_col;
    int opp_player = (player + 1) % 2;
    for (i = 0;i < 4;i++) {
        new_row = row + direction[i][0];
        new_col = col + direction[i][1];
        if (if_out(new_row,new_col))
            continue;
        if (gameMapVec[new_row][new_col] == opp_player) {
            if (!if_air(find(point_index(new_row,new_col),opp_player),opp_player)) //对手的某个group没有了“气”
                return true;
        }
    }
    return false;
}

bool GameModel::if_air(int group,int player)
{
    int i,j,k,new_i,new_j;
    for (i = 1;i < BOARD_GRAD_SIZE;i++) {
        for (j = 1;j < BOARD_GRAD_SIZE;j++) {//从1开始 边界没有air
            if (gameMapVec[i][j] == -1) { //扫描每一个空格
                for (k = 0;k < 4;k++) {
                    new_i = i + direction[k][0];
                    new_j = j + direction[k][1];
                    if (if_out(new_i,new_j))
                        continue;
                    if (gameMapVec[new_i][new_j] == player) {
                        if (find(point_index(new_i,new_j),player) == group)
                            return true;
                    }
                }
            }
        }
    }
    return false;
}



