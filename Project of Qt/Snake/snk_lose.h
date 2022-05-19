#ifndef SNK_LOSE_H
#define SNK_LOSE_H

#include <QWidget>

namespace Ui {
class SNK_LOSE;
}

class SNK_LOSE : public QWidget
{
    Q_OBJECT

public:
    explicit SNK_LOSE(QWidget *parent = nullptr);
    ~SNK_LOSE();

private:
    Ui::SNK_LOSE *ui;
};

#endif // SNK_LOSE_H
