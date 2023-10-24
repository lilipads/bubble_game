#include "game.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
    , m_board(new Board(kGridSize, this)) // Initialize Board instance
{}

QGraphicsScene *Game::gameScene() const
{
    return m_board->scene();
}
