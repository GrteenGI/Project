#include "mineblock.h"
#include "gameover.h"
#include <QPushButton>
#include "game.h"
#include <QDebug>
#include <QMouseEvent>
#include "win.h"


MineBlock::MineBlock(QWidget *parent)
    : QPushButton{parent}
{
    connect(this , &MineBlock::Been_Clicked , this ,[=](){      //触发被点击的信号后，翻开自己并翻开周围
        if(this->find == false){         //如果没被翻开
            this->Findthis();       //翻开自己
        }

    });
}

void MineBlock::Findthis(){     //翻开自己
    if(this->find) return;      //若该点被翻开，就return
    emit this->S_Findthis();
    if(this->val == -1){        //如果该点是雷
        this->find = true;
        GameOver * GMO = new GameOver;          //就GMO
        GMO->setWindowModality(Qt::ApplicationModal);       //模态化
        GMO->show();
        emit this->Over();
    }
    else if(this->val == 0){    //如果该点为空
        this->find = true;      //该点被翻开
        this->setStyleSheet("MineBlock{background-image: url(:/Mine/MineFind.png)}");   //设置背景图片
        emit this->FindOthers();        //触发翻开周围方格的信号
    }
    else{       //该点有值
        this->find = true;
        this->setStyleSheet("MineBlock{background-image: url(:/Mine/MineFind.png)}");   //设置背景图片
        this->setText(QString::number(this->val));      //展示该点的值
    }
}

void MineBlock::mousePressEvent(QMouseEvent *e){        //重写单击事件
    if(e->buttons() == Qt::LeftButton | Qt::RightButton){      //如果是左右键摁下
        emit this->LR_Clicked();        //触发左右键摁下信号
    }
    if(e->button() == Qt::RightButton){      //如果是右键
        if(this->find == true) return;      //如果已经被翻开，就return
        if(this->isflag == true){        //如果插了旗帜
            this->isflag = false;       //就变成未插旗状态
            emit this->Canel_Flag();        //触发取消旗帜信号
            this->setStyleSheet("MineBlock{background-image: url(:/Mine/MineUnFind.png)}");   //设置背景图片
        }
        else{
            this->isflag = true;        //变成插旗状态
            emit this->Been_SetFlag();      //触发被插棋信号
            this->setStyleSheet("MineBlock{background-image: url(:/Mine/SetFlag.png)}");   //设置背景图片
        }
    }
    else if(e->button() == Qt::LeftButton){     //如果是左键
        if(this->find == true) return;      //如果已经被翻开，就return
        if(this->isflag == true) return;        //如果该点有棋子，就无法点击
        emit this->Been_Clicked();     //触发单击信号
    }
}

void MineBlock::FindthisbyM(){     //翻开自己
    emit this->FindOthers();        //触发翻开周围方格的信号
}

