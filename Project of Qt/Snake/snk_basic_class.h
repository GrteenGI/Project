#ifndef SNK_BASIC_CLASS_H
#define SNK_BASIC_CLASS_H

#include <QObject>
#include <vector>
#include <QLabel>
#include <memory>
#include <QKeyEvent>
#include <QTimer>
#include <cstring>
#include <queue>

using namespace std;
class SNK_CRD;class SNK;class SNK_Candy;class SNK_snk;  //声明

const int _SNK_map_x = 22;      //地图的x轴长度
const int _SNK_map_y = 42;      //地图的y轴长度

const int _SNK_head_first_x = 10;       //蛇头初始位置
const int _SNK_head_first_y = 20;

const int dx[4] = { -1 , 0 , 1 , 0 };	//方向数组  上右下左
const int dy[4] = { 0 , 1 , 0 , -1 };

//坐标类
class SNK_CRD{
public:
    int _SNK_CRD_x;     //x轴坐标
    int _SNK_CRD_y;     //y轴坐标
    SNK_CRD() = default;
    ~SNK_CRD() = default;
    //构造函数
    SNK_CRD(int x , int y);
};

//主程序
class SNK{
public:
    //地图数组 用于记录信息
    int _SNK_map[_SNK_map_x][_SNK_map_y];
    //实际地图数组
    QLabel * _SNK_graph_map[_SNK_map_x][_SNK_map_y];
    //蛇容器
    vector<SNK_snk> _SNK_snake;
    //初始化地图
    void _SNK_init_map();
    //在实际地图中放入区块 (加载实际地图数组)
    void _SNK_push_block(int x , int y , QLabel& _push_block);
    //在地图上更新糖果位置
    void _SNK_update_candylocation(SNK_Candy *_update_target_candy);
    //随机生成糖果位置
    void _SNK_random_generate_candy(SNK_Candy * _update_candy);
    //更新真实地图
    void _SNK_update_map();
    //修改蛇头朝向
    void _SNK_change_head_toward(int _toward);
    //更新蛇的坐标
    void _SNK_update_snake();
    //添加蛇身
    void _SNK_add_body();
    //检测蛇头合法性
    bool _SNK_check_valid(int x , int y);
    //构造函数
    SNK();
};

//蛇类
class SNK_snk : public SNK_CRD{
public:
    //蛇头朝向 -1表示为蛇身
    int _SNK_snk_toward;
    //默认构造函数
    SNK_snk() = default;
    //构造函数 参数为朝向
    SNK_snk(int x , int y , int _head_toward);
    //析构函数
    ~SNK_snk() = default;
};

class SNK_Candy : public SNK_CRD{
public:
    int _SNK_Candy_score;      //糖果对应的分数
    int _SNK_Candy_lasttime;        //糖果持续的时间
    //默认构造函数
    SNK_Candy() = default;
    //构造函数  分数 持续时间
    SNK_Candy(int x , int y , int _score , int _lasttime);
    //析构函数
    ~SNK_Candy() = default;
};

#endif // SNK_BASIC_CLASS_H
