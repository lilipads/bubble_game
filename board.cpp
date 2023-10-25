#include "board.h"

#include <QRandomGenerator>
#include <queue>

Board::Board(int size, QWidget *parent)
    : QWidget(parent)
    , m_scene(new QGraphicsScene(this))
    , m_gridSize(size)
{
    initializeTiles();
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

void Board::onSelectEmptyTile(const Coordinate moveTo)
{
    if (m_move_from.has_value()) {
        getTile(*m_move_from)->ball()->stopAnimation();
        // Tries to move the ball.
        if (isValidMove(*m_move_from, moveTo)) {
            moveBall(*m_move_from, moveTo);
            m_move_from = std::nullopt;
            emit userTurnCompleted(moveTo);
        } else {
            m_move_from = std::nullopt;
        }
    }
}

void Board::onSelectBall(const Coordinate moveFrom)
{
    // If another ball is being selected, stop animating that ball.
    if (m_move_from.has_value()) {
        getTile(*m_move_from)->ball()->stopAnimation();
    }
    m_move_from = moveFrom;
}

void Board::onUnselectBall()
{
    m_move_from = std::nullopt;
}

bool Board::isValidMove(const Coordinate moveFrom, const Coordinate moveTo)
{
    // Uses BFS to check the existence of a path.
    const std::vector<Coordinate> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::queue<Coordinate> toExplore;
    QSet<Coordinate> visited;

    toExplore.push(moveFrom);
    visited.insert(moveFrom);

    while (!toExplore.empty()) {
        Coordinate current = toExplore.front();
        toExplore.pop();

        if (current == moveTo) {
            return true;
        }

        for (const Coordinate &direction : directions) {
            const Coordinate next = current + direction;
            if (isEmptyTile(next) && !visited.contains(next)) {
                visited.insert(next);
                toExplore.push(next);
            }
        }
    }
    return false;
}

bool Board::isEmptyTile(const Coordinate coordinate) const
{
    return m_empty_tiles.contains(coordinate);
}

Tile *Board::getTile(const Coordinate coordinate)
{
    if (coordinate.x < 0 || coordinate.x >= m_gridSize || coordinate.y < 0
        || coordinate.y >= m_gridSize) {
        throw std::out_of_range("Value out of allowed range");
    }
    return m_tiles[coordinate.x][coordinate.y];
}

std::optional<Coordinate> Board::getRandomEmptyGrid()
{
    if (m_empty_tiles.isEmpty()) {
        return std::nullopt;
    }

    const QList<Coordinate> list = m_empty_tiles.values();
    const int randomIndex = QRandomGenerator::global()->bounded(list.size());
    return list.at(randomIndex);
}

std::optional<BallColor> Board::getBallColor(Coordinate coordinate)
{
    const Tile *tile;
    try {
        tile = getTile(coordinate);
    } catch (const std::out_of_range &e) {
        return std::nullopt;
    }
    if (!tile->hasBall()) {
        return std::nullopt;
    }
    return tile->ball()->color();
}
