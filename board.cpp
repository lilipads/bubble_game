#include "board.h"

Board::Board(int size, QWidget *parent)
    : QWidget(parent)
    , m_scene(new QGraphicsScene(this))
    , m_gridSize(size)
{
    initializeTiles();
    initializeBallTracker();
    addBall(Qt::black, 0, 0);
}

QGraphicsScene *Board::scene() const
{
    return m_scene;
}

void Board::initializeTiles()
{
    m_tiles = new Tile **[m_gridSize];
    for (int x = 0; x < m_gridSize; ++x) {
        m_tiles[x] = new Tile *[m_gridSize];
        for (int y = 0; y < m_gridSize; ++y) {
            Tile *tile = new Tile({.x = x, .y = y});
            m_tiles[x][y] = tile;
            m_scene->addItem(tile);
        }
    }
}

void Board::initializeBallTracker()
{
    m_ball_tracker = new Ball **[m_gridSize];
    for (int x = 0; x < m_gridSize; ++x) {
        m_ball_tracker[x] = new Ball *[m_gridSize];
        for (int y = 0; y < m_gridSize; ++y) {
            m_ball_tracker[x][y] = nullptr;
        }
    }
}

void Board::addBall(const QColor color, const int x, const int y)
{
    if (!(x >= 0 && x < m_gridSize && y >= 0 && y < m_gridSize)) {
        return;
    }
    if (!m_ball_tracker[x][y]) { // Check if there's no ball already at the position
        Ball *ball = new Ball(color, m_tiles[x][y]);
        m_ball_tracker[x][y] = ball;
        m_scene->addItem(ball);
    }
}
