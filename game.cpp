#include "game.h"

Game::Game(QObject *parent)
    : QObject(parent)
    , m_board(new Board(gridSize, this)) // Initialize Board instance
{}

QGraphicsScene *Game::gameScene() const
{
    return m_board->scene();
}
