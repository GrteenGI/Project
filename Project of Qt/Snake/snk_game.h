#ifndef SNK_GAME_H
#define SNK_GAME_H

#include <QWidget>
#include "snk_basic_class.h"

namespace Ui {
class SNK_GAME;
}

class SNK_GAME : public QWidget
{
    Q_OBJECT

public:
    explicit SNK_GAME(QWidget *parent = nullptr);
    ~SNK_GAME();
    //初始化真实地图 , 并放入主程序的真实地图数组中
    void _SNK_GAME_init_map(SNK *_for_update_main);
    //初始化蛇头
    void _SNK_GAME_init_snkhead(SNK * for_update_main);
    //重写键盘事件
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::SNK_GAME *ui;

signals:
    //摁下键盘信号
    void _SNK_GAME_pressed_W();
    void _SNK_GAME_pressed_S();
    void _SNK_GAME_pressed_D();
    void _SNK_GAME_pressed_A();
};

#endif // SNK_GAME_H
