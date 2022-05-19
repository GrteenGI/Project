#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void _Widget_generate_SNK_GAME();       //生成游戏窗口

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
