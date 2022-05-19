#ifndef SNK_AUTO_GAME_H
#define SNK_AUTO_GAME_H

#include <QWidget>
#include "snk_basic_class.h"
#include "snk_game.h"

namespace Ui {
class SNK_AUTO_GAME;
}

class SNK_AUTO_GAME :public SNK_GAME
{
    Q_OBJECT

public:
    explicit SNK_AUTO_GAME(QWidget *parent = nullptr);
    ~SNK_AUTO_GAME();

private:
    Ui::SNK_AUTO_GAME *ui;
};

#endif // SNK_AUTO_GAME_H
