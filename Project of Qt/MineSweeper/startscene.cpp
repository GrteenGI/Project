#include "startscene.h"
#include "ui_startscene.h"
#include <QAction>
#include <QPushButton>
#include <QEvent>
#include "newgamechoice.h"

StartScene::StartScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartScene)
{

    ui->setupUi(this);
    connect(ui->actionExit , &QAction::triggered , this , [=](){    //单击exit就退出
        this->close();
    });

    connect(ui->actionNewGame , &QAction::triggered , this , [=](){     //难度选项窗口
        NewGameChoice * NewGame = new NewGameChoice();
        NewGame->setWindowModality(Qt::ApplicationModal);       //模态化
        NewGame->show();
    });
}

StartScene::~StartScene()
{
    delete ui;
}

