#include "game.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
    , m_board(new Board(kGridSize, this)) // Initialize Board instance
{}

QGraphicsScene *Game::gameScene() const
{
    return m_board->scene();
}

void Game::scoreAndUpdateBoard(const Coordinate coordinate)
{
    const int delta_score = getDeltaScoreAndEliminateLines(coordinate);
    m_score += delta_score;
    if (delta_score == 0) {
        addNewBalls();
    }
}

void Game::addNewBalls()
{
    // TODO: add balls
    displayNextBatchColors();
}

int Game::getDeltaScoreAndEliminateLines(const Coordinate coordinate)
{
    const int delta_score = 0;
    // Horizontal.
    // Vertical.
    // Forward slash.
    // Backward slach.
    if (delta_score > 0) {
        // Removes the origin.
    }
    return delta_score;
}
