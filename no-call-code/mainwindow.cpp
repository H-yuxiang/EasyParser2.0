#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font("Arial", 20, QFont::Bold);
    // 设置字体属性
    font.setItalic(true);
    font.setUnderline(true);
//    font.setStrikeOut(true);
    this->ui->label->setFont(font);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_exit_clicked()
{
    this->close();
}

void MainWindow::on_next_clicked()
{
    this->close();
    rules *second = new rules();
    second->show();
}
