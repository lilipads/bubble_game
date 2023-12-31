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
    ui->undoButton->setDisabled(true);
    connect(ui->undoButton, &QPushButton::clicked, this, &MainWindow::onUndoButtonClicked);
    connect(m_game, &Game::gameTurnCompleted, this, &MainWindow::onGameTurnCompleted);
    m_record_score = getRecordScore();
    ui->recordScoreBox->display(m_record_score);
}

void MainWindow::onNewGameButtonClicked()
{
    if (m_game != nullptr) {
        delete m_game;
        m_game = new Game(this);
    }
    initializeUi();
}

void MainWindow::onUndoButtonClicked()
{
    m_game->undo();
    ui->undoButton->setDisabled(true);
}

void MainWindow::onGameTurnCompleted(int score)
{
    ui->scoreBox->display(score);
    maybeUpdateRecordScore(score);
    ui->undoButton->setDisabled(false);
}

void MainWindow::maybeUpdateRecordScore(int score)
{
    if (score > m_record_score) {
        m_record_score = score;
        m_settings.setValue(m_record_score_key, score);
        ui->recordScoreBox->display(score);
    }
}

int MainWindow::getRecordScore() const
{
    return m_settings.value(m_record_score_key, 0).toInt();
}
