#include "rules.h"
#include "ui_rules.h"

rules::rules(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rules)
{
    ui->setupUi(this);
}

rules::~rules()
{
    delete ui;
}

void rules::on_back_clicked()
{
    this->close();
    MainWindow *mainwindow = new MainWindow();
    mainwindow->show();
}

void rules::on_next_clicked()
{
    this->close();
    action *act = new action();
    act->show();
}
