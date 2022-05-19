#ifndef NEWGAMECHOICE_H
#define NEWGAMECHOICE_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class NewGameChoice;
}

class NewGameChoice : public QWidget
{
    Q_OBJECT

public:
    explicit NewGameChoice(QWidget *parent = nullptr);
    ~NewGameChoice();

private:
    Ui::NewGameChoice *ui;
};

#endif // NEWGAMECHOICE_H
