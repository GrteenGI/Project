#ifndef MINEBLOCK_H
#define MINEBLOCK_H

#include <QWidget>
#include <QPushButton>
#include <QEvent>

class MineBlock : public QPushButton
{
    Q_OBJECT
public:
    explicit MineBlock(QWidget *parent = nullptr);

    int val;  //值 0为空 -1为雷

    bool find = false;   //表示该方格是否被翻开

    int m_x , m_y;      //x位置和y位置

    void Findthis();    //揭露该方块的数值

    void FindthisbyM();    //中键触发的揭露该方块数值

    void mousePressEvent(QMouseEvent *e);       //重写单击事件

    bool isflag = false;        //是否插了旗帜

    int flagnum = 0;        //该方格周围的旗帜数量

    //槽函数



signals:
    void Been_Clicked();       //信号，表示被点击了
    void S_Findthis();        //信号，表示该方块被揭露
    void FindOthers();      //信号，揭露周围方块的数值
    void Over();    //结束信号
    void Been_SetFlag();        //被插旗信号
    void Canel_Flag();      //取消旗帜信号
    void LR_Clicked();      //左右键同时摁下信号
};

#endif // MINEBLOCK_RH
