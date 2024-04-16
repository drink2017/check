#include "newcheck.h"
#include "ui_newcheck.h"

newCheck::newCheck(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::newCheck)
{
    ui->setupUi(this);
}

newCheck::~newCheck()
{
    delete ui;
}

