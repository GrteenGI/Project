#ifndef EASYGAME_H
#define EASYGAME_H

#include <QWidget>
#include <mineblock.h>
#include "game.h"

namespace Ui {
class EasyGame;
}

class EasyGame : public Game
{
    Q_OBJECT

public:
    explicit EasyGame(QWidget *parent = nullptr);
    ~EasyGame();

    void Stop();       //槽函数，游戏结束函数


private:
    Ui::EasyGame *ui;
};

#endif // EASYGAME_H
