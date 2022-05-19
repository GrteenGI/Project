#ifndef HARDGAME_H
#define HARDGAME_H

#include <QWidget>
#include "game.h"

namespace Ui {
class HardGame;
}

class HardGame : public Game
{
    Q_OBJECT

public:
    explicit HardGame(QWidget *parent = nullptr);
    ~HardGame();

    void Stop();        //槽函数  停止

private:
    Ui::HardGame *ui;
};

#endif // HARDGAME_H
