#ifndef NORMALGAME_H
#define NORMALGAME_H

#include <QWidget>
#include <mineblock.h>
#include "game.h"

namespace Ui {
class NormalGame;
}

class NormalGame : public Game
{
    Q_OBJECT

public:
    explicit NormalGame(QWidget *parent = nullptr);
    ~NormalGame();

    void Stop();       //槽函数，游戏结束函数

private:
    Ui::NormalGame *ui;
};

#endif // NORMALGAME_H
