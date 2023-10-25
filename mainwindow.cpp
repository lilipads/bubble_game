#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_game(new Game(this))
{
    ui->setupUi(this);
    ui->boardGraphicsView->setScene(m_game->boardScene());
    ui->panelGraphicsView->setScene(m_game->panelScene());
}

MainWindow::~MainWindow()
{
    delete ui;
}
