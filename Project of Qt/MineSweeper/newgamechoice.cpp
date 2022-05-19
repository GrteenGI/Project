#include "newgamechoice.h"
#include "ui_newgamechoice.h"
#include "easygame.h"
#include "normalgame.h"
#include "hardgame.h"

NewGameChoice::NewGameChoice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewGameChoice)
{
    ui->setupUi(this);
    QButtonGroup *block_difficulty=new QButtonGroup(this);      //选择难度的RadioButton的分组
    block_difficulty->addButton(ui->easyButton);        //简单难度按钮
    block_difficulty->addButton(ui->normalbutton);      //普通难度按钮
    block_difficulty->addButton(ui->hardbutton);        //困难难度按钮

    connect(ui->Difficulty_choose_button , &QPushButton::clicked , this , [=](){        //单击确定，遍历所有难度选择的radiobutton
        if(ui->easyButton->isChecked()){
            EasyGame * EG = new EasyGame();
            EG->show();
            this->close();      //关闭窗口
        }
        else if(ui->normalbutton->isChecked()){
            NormalGame * NG = new NormalGame();
            NG->show();
            this->close();
        }
        else{
            HardGame * HG = new HardGame();
            HG->show();
            this->close();
        }
    });
}

NewGameChoice::~NewGameChoice()
{
    delete ui;
}
