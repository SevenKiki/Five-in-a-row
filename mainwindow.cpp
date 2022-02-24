#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "board.h"
#include "heuriatic.h"
#include "aiplay.h"
#include "sunafa3.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    board  * b = new board();//人人对战
    b->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    heuriatic * h = new heuriatic();//贪心
    h->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    AIplay *a = new AIplay();//minimax
    a->show();
}

