#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class StartScene; }
QT_END_NAMESPACE

class StartScene : public QMainWindow
{
    Q_OBJECT

public:
    StartScene(QWidget *parent = nullptr);
    ~StartScene();



private:
    Ui::StartScene *ui;
};
#endif // STARTSCENE_H
