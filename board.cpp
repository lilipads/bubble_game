#include "board.h"

#include <QRandomGenerator>

Board::Board(int size, QWidget *parent)
    : QWidget(parent)
    , m_scene(new QGraphicsScene(this))
    , m_gridSize(size)
{
    initializeTiles();
    addBall(BallColor::Red, {.x = 1, .y = 2});
    addBall(BallColor::Blue, {.x = 3, .y = 6});
    addBall(BallColor::Green, {.x = 0, .y = 0});
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
            const Coordinate coordinate = {.x = x, .y = y};
            Tile *tile = new Tile(coordinate);
            tile->setPos(x * tile->size(), y * tile->size());
            m_tiles[x][y] = tile;
            m_scene->addItem(tile);
            connect(tile, &Tile::selectEmptyTile, this, &Board::onSelectEmptyTile);
            connect(tile, &Tile::selectBall, this, &Board::onSelectBall);
            connect(tile, &Tile::unselectBall, this, &Board::onUnselectBall);
            m_empty_tiles.insert(coordinate);
        }
    }
}

void Board::addBall(const BallColor color, const Coordinate coordinate)
{
    Tile *tile = getTile(coordinate);
    Ball *ball = new Ball(color, tile->size());
    tile->setBall(ball);
    m_empty_tiles.remove(coordinate);
}

void Board::removeBall(const Coordinate coordinate)
{
    Tile *fromTile = getTile(coordinate);
    fromTile->removeBall();
    m_empty_tiles.insert(coordinate);
}

void Board::moveBall(const Coordinate from, const Coordinate to)
{
    BallColor color = getTile(from)->ball()->color();
    addBall(color, to);
    removeBall(from);
}

void Board::onSelectEmptyTile(const Coordinate move_to)
{
    if (m_move_from.has_value()) {
        getTile(*m_move_from)->ball()->stopAnimation();
        // Tries to move the ball.
        if (isValidMove(*m_move_from, move_to)) {
            moveBall(*m_move_from, move_to);
            m_move_from = std::nullopt;
            emit userTurnCompleted(move_to);
        }
    }
}

void Board::onSelectBall(const Coordinate move_from)
{
    // If another ball is being selected, stop animating that ball.
    if (m_move_from.has_value()) {
        getTile(*m_move_from)->ball()->stopAnimation();
    }
    m_move_from = move_from;
}

void Board::onUnselectBall()
{
    m_move_from = std::nullopt;
}

bool Board::isValidMove(const Coordinate move_from, const Coordinate move_to)
{
    // TODO
    return true;
}

Tile *Board::getTile(const Coordinate coordinate)
{
    if (coordinate.x < 0 || coordinate.x >= m_gridSize || coordinate.y < 0
        || coordinate.y >= m_gridSize) {
        throw std::out_of_range("Value out of allowed range");
    }
    return m_tiles[coordinate.x][coordinate.y];
}

std::optional<Coordinate> Board::getEmptyGrid()
{
    if (m_empty_tiles.isEmpty()) {
        return std::nullopt;
    }

    const QList<Coordinate> list = m_empty_tiles.values();
    const int randomIndex = QRandomGenerator::global()->bounded(list.size());
    return list.at(randomIndex);
}
