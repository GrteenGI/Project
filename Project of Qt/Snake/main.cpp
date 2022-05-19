#include "widget.h"
#include <QApplication>
#include <time.h>

int main(int argc, char *argv[])
{
    srand((unsigned)time(NULL));        //生成时间种子 用于生成糖果
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
