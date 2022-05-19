#include "snk_auto_game.h"
#include "ui_snk_auto_game.h"
#include "snk_basic_class.h"
using namespace std;

SNK_AUTO_GAME::SNK_AUTO_GAME(QWidget *parent) :
    SNK_GAME(parent),
    ui(new Ui::SNK_AUTO_GAME)
{
    ui->setupUi(this);
    //初始化大小
    this->setFixedHeight(660);
    this->setFixedWidth(1260);
    //启动主程序
    SNK *Main = new SNK();
    //更新计时器对象
    QTimer * _SNK_update_timer = new QTimer(this);
    SNK_Candy * candy = new SNK_Candy();        //糖果

    connect(_SNK_update_timer , &QTimer::timeout , this , [=]()mutable{
        Main->_SNK_BFS(candy);
        Main->_SNK_dfs_roads.clear();
        int tempx = Main->_SNK_snake.begin()->_SNK_CRD_x;
        int tempy = Main->_SNK_snake.begin()->_SNK_CRD_y;
        Main->_SNK_DFS(Main->_SNK_snake.front() , candy);
        Main->_SNK_snake.begin()->_SNK_CRD_x = tempx;
        Main->_SNK_snake.begin()->_SNK_CRD_y = tempy;
        for(auto it : Main->_SNK_dfs_roads){
            Main->_SNK_snake.begin()->_SNK_snk_toward = it;
            Main->_SNK_update_snake();
            Main->_SNK_update_map();
        }
        //如果吃到了糖果
        if(Main->_SNK_snake.begin()->_SNK_CRD_x == candy->_SNK_CRD_x && Main->_SNK_snake.begin()->_SNK_CRD_y == candy->_SNK_CRD_y){
            Main->_SNK_random_generate_candy(candy);        //重新随机一颗新的糖果
            Main->_SNK_add_body();
        }
        Main->_SNK_update_map();
    });

    Main->_SNK_random_generate_candy(candy);      //随机生成糖果位置
    this->_SNK_GAME_init_snkhead(Main);        //初始化蛇头
    this->_SNK_GAME_init_map(Main);        //初始化地图

    _SNK_update_timer->start(200);
}

SNK_AUTO_GAME::~SNK_AUTO_GAME()
{
    delete ui;
}
