#include "snk_basic_class.h"
#include <cstring>
#include <time.h>
#include <QTimer>
using namespace std;

//初始化地图
void SNK::_SNK_init_map(){
    //初始化地图为0
    memset(this->_SNK_map , 0 , sizeof(_SNK_map));
    //标记边界
    for(int i = 0 ; i <= _SNK_map_x - 1 ; i++){
        this->_SNK_map[i][0] = 1;       //1表示地图边界
        this->_SNK_map[i][41] = 1;
    }
    for(int i = 0 ; i <= _SNK_map_y - 1 ; i++){
        this->_SNK_map[0][i] = 1;
        this->_SNK_map[21][i] = 1;
    }
}

//更新糖果当前位置
void SNK::_SNK_update_candylocation(SNK_Candy *_update_target_candy){
    //3表示糖果
    this->_SNK_map[_update_target_candy->_SNK_CRD_x][_update_target_candy->_SNK_CRD_y] = 3;
}

//加载实际区块数组
void SNK::_SNK_push_block(int x , int y , QLabel& _push_block){
    this->_SNK_graph_map[x][y] = &_push_block;
}

//随机生成糖果位置
void SNK::_SNK_random_generate_candy(SNK_Candy * _update_candy){
    int first = 1 + rand() % 20;		//x
    int second = 1 + rand() % 40;		//y
    while (this->_SNK_map[first][second] != 0) {		//如果该区块不为空
        first = 1 + rand() % 20;		//就重置
        second = 1 + rand() % 40;
    }
    this->_SNK_map[first][second] = 3;      //该区块为糖果
    _update_candy->_SNK_CRD_x = first;
    _update_candy->_SNK_CRD_y = second;
}

//更新真实地图
void SNK::_SNK_update_map(){
    for(int i = 0 ; i <= _SNK_map_x - 1 ; i++)
        for(int j = 0 ; j <= _SNK_map_y - 1 ; j++){
            if(this->_SNK_map[i][j] == 1)
                this->_SNK_graph_map[i][j]->setStyleSheet("QLabel{background-image: url(:/Block/rec_block/Block_blocker.png)}");
            else if(this->_SNK_map[i][j] == 0)  //如果没有任何东西
                this->_SNK_graph_map[i][j]->setStyleSheet("QLabel{background-image: url(:/Block/rec_block/Block_space.png)}");
            else if(this->_SNK_map[i][j] == 4)  //如果是蛇头
                this->_SNK_graph_map[i][j]->setStyleSheet("QLabel{background-image: url(:/Snake/rec_snake/Snake_head.jpg)}");
            else if(this->_SNK_map[i][j] == 2)   //如果是蛇身
                this->_SNK_graph_map[i][j]->setStyleSheet("QLabel{background-image: url(:/Snake/rec_snake/Snake_body.png)}");
            else    //如果是糖果
                this->_SNK_graph_map[i][j]->setStyleSheet("QLabel{background-image: url(:/Block/rec_block/Candy.jpg)}");
        }
}

//修改蛇头朝向
void SNK::_SNK_change_head_toward(int _toward){

    if(this->_SNK_snake.size() > 1){
        //如果设置的朝向不是朝后(就当前朝向而言)
        if(this->_SNK_map[this->_SNK_snake.front()._SNK_CRD_x + dx[_toward]][this->_SNK_snake.front()._SNK_CRD_y + dy[_toward]] != 2)
            this->_SNK_snake.front()._SNK_snk_toward = _toward;     //修改蛇头朝向为设置的朝向
    }
    else{
        this->_SNK_snake.front()._SNK_snk_toward = _toward;   //修改蛇头朝向为设置的朝向
    }

}

//更新蛇的位置
void SNK::_SNK_update_snake(){
    auto head = this->_SNK_snake.begin();
    this->_SNK_map[this->_SNK_snake.back()._SNK_CRD_x][this->_SNK_snake.back()._SNK_CRD_y] = 0;
    for(auto it = prev(this->_SNK_snake.end()) ; it != this->_SNK_snake.begin() ; it--){
        it->_SNK_CRD_x = prev(it)->_SNK_CRD_x;
        it->_SNK_CRD_y = prev(it)->_SNK_CRD_y;
    }
    this->_SNK_map[head->_SNK_CRD_x][head->_SNK_CRD_y] = 0;
    head->_SNK_CRD_x += dx[head->_SNK_snk_toward];
    head->_SNK_CRD_y += dy[head->_SNK_snk_toward];
    this->_SNK_map[head->_SNK_CRD_x][head->_SNK_CRD_y] = 4;
    for(auto it = this->_SNK_snake.begin() ; it != this->_SNK_snake.end() ; it++){
        if(it != this->_SNK_snake.begin()){
            this->_SNK_map[it->_SNK_CRD_x][it->_SNK_CRD_y] = 2;
        }
    }
}

//添加蛇身体
void SNK::_SNK_add_body(){
    int _add_body_x = 0;        //待添加身体的坐标
    int _add_body_y = 0;
    //如果只有蛇头
    if(this->_SNK_snake.size() == 1){
        _add_body_x = this->_SNK_snake.begin()->_SNK_CRD_x - dx[this->_SNK_snake.begin()->_SNK_snk_toward];
        _add_body_y = this->_SNK_snake.begin()->_SNK_CRD_y - dy[this->_SNK_snake.begin()->_SNK_snk_toward];
    }
    else{       //不止有蛇头
        _add_body_x = 2 * this->_SNK_snake.back()._SNK_CRD_x - (this->_SNK_snake.end() - 2)->_SNK_CRD_x;
        _add_body_y = 2 * this->_SNK_snake.back()._SNK_CRD_y - (this->_SNK_snake.end() - 2)->_SNK_CRD_y;
    }
    //创建蛇身R
    SNK_snk * _add_body = new SNK_snk(_add_body_x , _add_body_y , -1);
    this->_SNK_snake.push_back(*_add_body);
}

//检测蛇头合法性
bool SNK::_SNK_check_valid(int x , int y){
    if(this->_SNK_map[x][y] == 1 || this->_SNK_map[x][y] == 2)
        return false;
    return true;
}

//构造函数
SNK::SNK(){
    //初始化地图
    this->_SNK_init_map();
}

//构造函数
SNK_snk::SNK_snk(int x , int y , int _head_toward){
    //设置朝向 -1为蛇身
    this->_SNK_snk_toward = _head_toward;
    this->_SNK_CRD_x = x;
    this->_SNK_CRD_y = y;
}
//构造函数
SNK_Candy::SNK_Candy(int x , int y , int _score , int _lasttime){
    this->_SNK_Candy_score = _score;
    this->_SNK_Candy_lasttime = _lasttime;
    this->_SNK_CRD_x = x;
    this->_SNK_CRD_y = y;
}

//构造函数
SNK_CRD::SNK_CRD(int x , int y){
    this->_SNK_CRD_x = x;
    this->_SNK_CRD_y = y;
}


