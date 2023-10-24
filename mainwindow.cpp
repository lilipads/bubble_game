#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_game(new Game(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(m_game->gameScene());
}

MainWindow::~MainWindow()
{
    delete ui;
}
