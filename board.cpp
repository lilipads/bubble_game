#include "board.h"

Board::Board(int size, QWidget *parent)
    : QWidget(parent)
    , m_scene(new QGraphicsScene(this))
    , m_gridSize(size)
{
    initializeTiles();
    addBall(Qt::black, 1, 2);
    addBall(Qt::blue, 3, 6);
    addBall(Qt::red, 0, 0);
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
            tile->setPos(x * tile->size(), y * tile->size());
            m_tiles[x][y] = tile;
            m_scene->addItem(tile);
            connect(tile, &Tile::onClick, this, &Board::handleTileClick);
        }
    }
}

void Board::addBall(const QColor color, const int x, const int y)
{
    // Returns if the coordinate is invalid.
    if (!(x >= 0 && x < m_gridSize && y >= 0 && y < m_gridSize)) {
        return;
    }
    Ball *ball = new Ball(color, m_tiles[x][y]->size());
    m_tiles[x][y]->setBall(ball);
    connect(ball, &Ball::onSelect, this, &Board::handleBallSelect);
    connect(ball, &Ball::onUnselect, this, &Board::handleBallUnselect);
}

void Board::handleTileClick(Coordinate pos)
{
    qDebug() << "Tile clicked at coordinate:" << pos.x << pos.y;
}

void Board::handleBallSelect(Coordinate pos)
{
    qDebug() << "Ball selected at coordinate:" << pos.x << pos.y;
}

void Board::handleBallUnselect()
{
    qDebug() << "Ball unselected at coordinate";
}
