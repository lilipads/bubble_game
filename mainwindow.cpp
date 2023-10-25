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
    connect(ui->newGameButton, &QPushButton::clicked, this, &MainWindow::onNewGameButtonClicked);
    connect(m_game, &Game::scoreUpdated, this, &MainWindow::onScoreUpdated);
}

void MainWindow::onNewGameButtonClicked()
{
    if (m_game != nullptr) {
        delete m_game;
        m_game = new Game(this);
    }
    initializeUi();
}

void MainWindow::onScoreUpdated(int score)
{
    ui->scoreBox->display(score);
    // TODO: save the current score
}
