#include "game.h"
#include <algorithm>
#include <QFile>

Game::Game(QWidget *parent)
    : QWidget{parent}
{
}

bool Game::Checkinmap(int i, int j ,int width ,int height){
    if(i < 1 || j < 1 || i > height || j > width) return false;
    return true;
}


void Game::CountRoundMine(int i ,int j ,int width ,int height){        //统计一个格子周围的雷数
    if(this->Map[i][j]->val == -1) return;    //如果该格子是雷，则直接返回
    for(int k = 0; k < 9 ; k++){
        if(this->Checkinmap(i+dx[k],j+dy[k] , width , height) == false){  //在地图外就continue
            continue;
        }
        if(this->Map[i+dx[k]][j+dy[k]]->val == -1){  //遍历周围格子，如果是雷，则数值+1
            this->Map[i][j]->val++;
        }
    }
}

