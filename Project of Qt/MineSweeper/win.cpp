#include "win.h"
#include "ui_win.h"

Win::Win(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Win)
{
    ui->setupUi(this);
    //帅字
    ui->label->setAlignment(Qt::AlignHCenter);
    QFont Handsome;
    Handsome.setPointSize(50);
    ui->label->setFont(Handsome);
}

Win::~Win()
{
    delete ui;
}
