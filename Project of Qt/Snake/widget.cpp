#include "widget.h"
#include "ui_widget.h"
#include "snk_game.h"
#include "snk_auto_game.h"
#include "snk_basic_class.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //单击start按钮生成游戏界面
    connect(ui->_Widget_start , &QPushButton::clicked , this , &Widget::_Widget_generate_SNK_GAME);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::_Widget_generate_SNK_GAME(){       //生成游戏窗口
    SNK_GAME * Snk_game_widget = new SNK_GAME();
    Snk_game_widget->show();
}

