#include "snk_game.h"
#include "ui_snk_game.h"
#include "snk_basic_class.h"
#include <QDebug>

using namespace std;

SNK_GAME::SNK_GAME(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SNK_GAME)
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
    //连接键盘摁下信号和改变蛇头方向的函数
    connect(this , &SNK_GAME::_SNK_GAME_pressed_W , this , [=]()mutable{
        Main->_SNK_change_head_toward(0);
    });
    connect(this , &SNK_GAME::_SNK_GAME_pressed_D , this , [=]()mutable{
        Main->_SNK_change_head_toward(1);
    });
    connect(this , &SNK_GAME::_SNK_GAME_pressed_S , this , [=]()mutable{
        Main->_SNK_change_head_toward(2);
    });
    connect(this , &SNK_GAME::_SNK_GAME_pressed_A , this , [=]()mutable{
        Main->_SNK_change_head_toward(3);
    });

    connect(_SNK_update_timer , &QTimer::timeout , this , [=]()mutable{
        //如果下一步不合法
        if(!Main->_SNK_check_valid(Main->_SNK_snake.begin()->_SNK_CRD_x + dx[Main->_SNK_snake.begin()->_SNK_snk_toward] , Main->_SNK_snake.begin()->_SNK_CRD_y + dy[Main->_SNK_snake.begin()->_SNK_snk_toward])){
            _SNK_update_timer->stop();
        }
        Main->_SNK_update_snake();      //更新蛇的信息
        //如果吃到了糖果
        if(Main->_SNK_snake.begin()->_SNK_CRD_x == candy->_SNK_CRD_x && Main->_SNK_snake.begin()->_SNK_CRD_y == candy->_SNK_CRD_y){
            Main->_SNK_random_generate_candy(candy);        //重新随机一颗新的糖果
            Main->_SNK_add_body();
        }
        Main->_SNK_update_map();       //更新地图样式
    });

    Main->_SNK_random_generate_candy(candy);      //随机生成糖果位置
    this->_SNK_GAME_init_snkhead(Main);        //初始化蛇头
    this->_SNK_GAME_init_map(Main);        //初始化地图

    _SNK_update_timer->start(100);
}

SNK_GAME::~SNK_GAME()
{
    delete ui;
}

//初始化真实地图 , 并放入主程序的真实地图数组中
void SNK_GAME::_SNK_GAME_init_map(SNK *_for_update_main){
    for(int i = 0 ; i <= _SNK_map_x - 1; i++)
        for(int j = 0 ; j <= _SNK_map_y - 1; j++){
            QLabel *Block = new QLabel(this);
            Block->setMinimumHeight(30);
            Block->setMinimumWidth(30);
            //如果是边界
            if(_for_update_main->_SNK_map[i][j] == 1)
                Block->setStyleSheet("QLabel{background-image: url(:/Block/rec_block/Block_blocker.png)}");
            else if(_for_update_main->_SNK_map[i][j] == 0)  //如果没有任何东西
                Block->setStyleSheet("QLabel{background-image: url(:/Block/rec_block/Block_space.png)}");
            else if(_for_update_main->_SNK_map[i][j] == 4)  //如果是蛇头
                Block->setStyleSheet("QLabel{background-image: url(:/Snake/rec_snake/Snake_head.jpg)}");
            else if(_for_update_main->_SNK_map[i][j] == 2)   //如果是蛇身
                Block->setStyleSheet("QLabel{background-image: url(:/Snake/rec_snake/Snake_body.png)}");
            else    //如果是糖果
                Block->setStyleSheet("QLabel{background-image: url(:/Block/rec_block/Candy.jpg)}");

            //修改位置
            Block->move(30 * j , 30 * i);
            //将区块放入主程序区块数组中
            _for_update_main->_SNK_push_block(i , j , *Block);

            _for_update_main->_SNK_graph_map[i][j]->show();
        }
}
//初始化蛇头
void SNK_GAME::_SNK_GAME_init_snkhead(SNK * for_update_main){
    //创建蛇头
    SNK_snk * snk_head = new SNK_snk(_SNK_head_first_x , _SNK_head_first_y , 1);
    //将蛇头放入主程序的蛇容器中
    for_update_main->_SNK_snake.push_back(*snk_head);
    //更新地图
    for_update_main->_SNK_map[_SNK_head_first_x][_SNK_head_first_y] = 4;    //4为蛇头
}

void SNK_GAME::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_W)
        emit this->_SNK_GAME_pressed_W();
    else if(event->key() == Qt::Key_S)
        emit this->_SNK_GAME_pressed_S();
    else if(event->key() == Qt::Key_D)
        emit this->_SNK_GAME_pressed_D();
    else if(event->key() == Qt::Key_A)
        emit this->_SNK_GAME_pressed_A();
}
