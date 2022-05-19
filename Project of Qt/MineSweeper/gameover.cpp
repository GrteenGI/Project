#include "gameover.h"
#include "ui_gameover.h"
#include <QFont>

GameOver::GameOver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameOver)
{
    ui->setupUi(this);
    //菜字
    ui->label->setAlignment(Qt::AlignHCenter);
    QFont cai;
    cai.setPointSize(50);
    ui->label->setFont(cai);


    connect(ui->pushButton , &QPushButton::clicked,this ,[=](){     //啊对对对后退出
        this->close();
    });
}

GameOver::~GameOver()
{
    delete ui;
}
