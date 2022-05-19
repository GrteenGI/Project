#include "startscene.h"

#include <QApplication>
#include "newgamechoice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartScene w;
    w.show();
    return a.exec();
}
