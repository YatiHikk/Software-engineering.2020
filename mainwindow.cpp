#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "creature.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this ->setWindowFlag(Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    this->hide();

    Creature creature;
    creature.exec();

    this->show();
}
