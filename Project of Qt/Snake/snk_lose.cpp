#include "snk_lose.h"
#include "ui_snk_lose.h"

SNK_LOSE::SNK_LOSE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SNK_LOSE)
{
    ui->setupUi(this);
}

SNK_LOSE::~SNK_LOSE()
{
    delete ui;
}
