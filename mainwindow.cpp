#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_game(new Game(this))
{
    initializeUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeUi()
{
    ui->setupUi(this);
    ui->boardGraphicsView->setScene(m_game->boardScene());
    ui->panelGraphicsView->setScene(m_game->panelScene());
    connect(ui->newGameButton, &QPushButton::clicked, this, &MainWindow::on_new_game_button_clicked);
}

void MainWindow::on_new_game_button_clicked()
{
    // TODO: save the current score
    if (m_game != nullptr) {
        delete m_game;
        m_game = new Game(this);
    }
    initializeUi();
}
