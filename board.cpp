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
            connect(tile, &Tile::selectEmptyTile, this, &Board::onSelectEmptyTile);
            connect(tile, &Tile::selectBall, this, &Board::onSelectBall);
            connect(tile, &Tile::unselectBall, this, &Board::onUnselectBall);
        }
    }
}

// TODO: take in Position instead of raw x and y
void Board::addBall(const QColor color, const int x, const int y)
{
    // Returns if the coordinate is invalid.
    if (!(x >= 0 && x < m_gridSize && y >= 0 && y < m_gridSize)) {
        return;
    }
    Ball *ball = new Ball(color, m_tiles[x][y]->size());
    m_tiles[x][y]->setBall(ball);
}

void Board::onSelectEmptyTile(Coordinate coordinate)
{
    if (m_move_from.has_value()) {
        // stop animating
        // try to move
    }
    qDebug() << "Tile clicked at coordinate:" << coordinate.toString();
}

void Board::onSelectBall(Coordinate coordinate)
{
    // If another ball is being selected, stop animating that ball.
    if (m_move_from.has_value()) {
        getTile(*m_move_from)->ball()->stopAnimation();
    }
    m_move_from = coordinate;
    qDebug() << "Ball selected at coordinate:" << coordinate.toString();
}

void Board::onUnselectBall()
{
    m_move_from = std::nullopt;
    qDebug() << "Ball unselected.";
}

Tile *Board::getTile(Coordinate coordinate)
{
    return m_tiles[coordinate.x][coordinate.y];
}
