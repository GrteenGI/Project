#include "easygame.h"
#include "ui_easygame.h"
#include "mineblock.h"
#include <algorithm>
#include "gameover.h"
#include "win.h"
#include <time.h>
#include <QTimer>
#include <QFile>
#include <QTextEdit>
using namespace std;

EasyGame::EasyGame(QWidget *parent) :
    Game(parent),
    ui(new Ui::EasyGame)
{
    ui->setupUi(this);
    QTimer *t = new QTimer();
    ui->label->setText(QString::number(this->cnt));       //初始为0秒
    connect(t , &QTimer::timeout , this ,[=](){         //每隔一秒计时器增加一秒
        this->cnt++;
        ui->label->setText(QString::number(cnt));
    });
    for(int i = 1 ; i <= 9 ; i++)
        for(int j = 1 ; j <= 9 ; j++){
            MineBlock * M = new MineBlock(this);        //创建方块
            M->m_x = i;         //方块的相对x轴
            M->m_y = j;         //方块的相对y轴
            M->find = false;    //起初没被翻开
            M->setFixedWidth(45);       //大小
            M->setFixedHeight(45);
            M->move(22.5 + (i-1)*45 , 22.5 + (j - 1)*45);       //移动位置
            this->setStyleSheet("MineBlock{background-image: url(:/Mine/MineUnFind.png)}");   //设置背景图片
            this->Map[i][j] = M;  //放入map数组内
            connect(M , &MineBlock::FindOthers , this ,[=](){       //连接Findothers信号，翻开该方格周围的点
                for(int k = 0 ; k < 9 ; k++){
                    if(this->Checkinmap(i+dx[k],j+dy[k] , 9 , 9) == false){  //在地图外就continue
                        continue;
                    }
                    if(this->Map[M->m_x + dx[k]][M->m_y + dy[k]]->isflag) continue;
                    this->Map[M->m_x + dx[k]][M->m_y + dy[k]]->Findthis();
                }
            });

            connect(M , &MineBlock::Over , this , [=](){  //连接结束信号
                t->stop();
                this->Stop();
            });
            connect(M , &MineBlock::Been_SetFlag , this ,[=](){         //连接被插旗信号
                for(int k = 0 ; k < 9 ; k++){
                    if(this->Checkinmap(i+dx[k],j+dy[k] , 9 , 9) == false){  //在地图外就continue
                        continue;
                    }
                    this->Map[M->m_x + dx[k]][M->m_y + dy[k]]->flagnum++;           //遍历周围所有格子，跟新插旗数量
                    //qDebug() << this->Map[M->m_x + dx[k]][M->m_y + dy[k]]->flagnum << " " << this->Map[M->m_x + dx[k]][M->m_y + dy[k]]->val;
                }
            });

            connect(M , &MineBlock::Canel_Flag , this , [=](){      //连接取消旗帜信号
                for(int k = 0 ; k < 9 ; k++){
                    if(this->Checkinmap(i+dx[k],j+dy[k] , 9 , 9) == false){  //在地图外就continue
                        continue;
                    }
                    this->Map[M->m_x + dx[k]][M->m_y + dy[k]]->flagnum--;           //遍历周围所有格子，跟新插旗数量
                }
            });

            connect(M , &MineBlock::LR_Clicked , this , [=](){      //连接左右键同时摁下信号
                if(M->flagnum == M->val){      //如果旗帜数量等于其数值
                    M->FindthisbyM();          //就翻开它自己
                }
            });

            connect(M , &MineBlock::S_Findthis , this,[=](){            //连接被翻开信号
                if(this->RestUnMineNum == 9*9 - 10){      //如果是开局状态下的第一次点击
                    t->start(1000);         //开始计时
                    srand((unsigned)time(NULL));        //生成随机数
                    int Random_Mine[82];        //随机分配雷
                    memset(Random_Mine , 0 , sizeof(Random_Mine));
                    for(int i = 1 ; i <= 10 ; i++)
                        Random_Mine[i] = -1;        //-1为雷
                    random_shuffle(Random_Mine + 1 , Random_Mine + 81);     //打乱

                    int cnt = 1;
                    for(int i = 1 ; i <= 9 ; i++)
                        for(int j = 1 ; j <= 9 ; j++){
                            this->Map[i][j]->val = Random_Mine[cnt++];        //将雷分配
                        }

                    if(this->Map[M->m_x][M->m_y]->val == -1){       //如果第一次点击点为雷
                        this->Map[M->m_x][M->m_y]->val = -2 ;        //该点不为雷 -2保证后续的随机不会随机到该位置
                        while(1){
                            int randx = rand() % 9 + 1;             //随机找出不为雷的点
                            int randy = rand() % 9 + 1;
                            if(this->Map[randx][randy]->val == 0){
                                this->Map[randx][randy]->val = -1;
                                break;
                            }
                        }
                    }
                    for(int k = 0 ; k < 9 ; k++){           //第一次点击点周围区域均无雷
                        if(this->Checkinmap(i+dx[k],j+dy[k] , 9 , 9) == false){  //在地图外就continue
                            continue;
                        }
                        if(this->Map[M->m_x + dx[k]][M->m_y + dy[k]]->val == -1){       //如果该点为雷
                            this->Map[M->m_x + dx[k]][M->m_y + dy[k]]->val = -2 ;        //该点不为雷 -2保证后续的随机不会随机到该位置
                            while(1){
                                int randx = rand() % 9 + 1;             //随机找出不为雷的点
                                int randy = rand() % 9 + 1;
                                if(this->Map[randx][randy]->val == 0){
                                    this->Map[randx][randy]->val = -1;
                                    break;
                                }
                            }
                        }
                    }

                    for(int k = 0 ; k < 9 ; k++){
                        if(this->Checkinmap(i+dx[k],j+dy[k] , 9 , 9) == false){  //在地图外就continue
                            continue;
                        }
                        this->Map[M->m_x + dx[k]][M->m_y + dy[k]]->val = 0;      //该点无雷
                    }
                    for(int i = 1 ; i <= 9 ; i++){
                        for(int j = 1 ; j <= 9 ; j++){
                            this->CountRoundMine(i , j , 9 , 9);            //统计每个格子旁边有几颗雷
                        }
                    }
                }

                this->RestUnMineNum--;              //剩余的非雷格子数量减少
                if(this->RestUnMineNum == 0){           //如果非雷格子数量为0
                    t->stop();          //结束计时
                    Win * win = new Win;        //Win！
                    win->show();
                    emit M->Over();         //结束
                }
            });
        }

    this->RestUnMineNum = 9 * 9 - 10;


}

void EasyGame::Stop(){
    for(int i = 1 ; i <= 9 ; i++)
        for(int j = 1 ; j <= 9 ; j++){
            if(this->Map[i][j]->val == -1){     //如果是雷
                this->Map[i][j]->setStyleSheet("MineBlock{background-image: url(:/Mine/Mine.png)}");   //设置背景图片
            }
            else if(this->Map[i][j]->val != 0){
                this->Map[i][j]->setText(QString::number(Map[i][j]->val));
            }
            this->Map[i][j]->setEnabled(false);     //让所有按钮失效
        }
}

EasyGame::~EasyGame()
{
    delete ui;
}
