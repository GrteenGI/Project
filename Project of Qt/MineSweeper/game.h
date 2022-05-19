#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "mineblock.h"
#include <QTimer>
#include <QVector>

const int dx[9] ={-1 , -1 , -1 , 0 , 1 , 1 , 1 , 0};  //左上->右下
const int dy[9] ={-1 , 0 , 1 , 1 , 1 , 0 , -1 , -1};

class Game : public QWidget
{
    Q_OBJECT
public:
    friend MineBlock;
    explicit Game(QWidget *parent = nullptr);

    MineBlock* Map[100][100];

    bool Checkinmap(int i ,int j , int width ,int height);      //ij为方格坐标，width和height为地图大小

    int RestUnMineNum = 0;        //剩余的非雷格子的数量

    int cnt = 0;        //时间

    void CountRoundMine(int i ,int j , int width ,int height);  //统计一个格子周围的雷数

signals:

};

#endif // GAME_H
