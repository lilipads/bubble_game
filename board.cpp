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
    m_newly_added_balls.push_back(coordinate);
}

void Board::removeBall(const Coordinate coordinate)
{
    Tile *fromTile = getTile(coordinate);
    BallColor color;
    if (fromTile->hasBall()) {
        color = fromTile->ball()->color();
    }
    fromTile->removeBall();
    m_empty_tiles.insert(coordinate);
    m_newly_removed_balls.push_back(coordinate);
    m_newly_removed_ball_colors.push_back(color);
}

void Board::moveBall(const Coordinate from, const Coordinate to)
{
    BallColor color = getTile(from)->ball()->color();
    addBall(color, to);
    removeBall(from);
}

void Board::undo()
{
    // Makes a copy of the vectors so as we add and remove balls,
    // they don't get changed.
    std::vector<Coordinate> balls_to_add = m_newly_removed_balls;
    std::vector<BallColor> colors_of_balls_to_add = m_newly_removed_ball_colors;
    std::vector<Coordinate> balls_to_remove = m_newly_added_balls;

    // The order is relevant here: must add first and then remove. If a ball is
    // moved and then gets scored, it shows up in both the added list and the
    // removed list.
    for (int i = 0; i < balls_to_add.size() && i < colors_of_balls_to_add.size(); ++i) {
        addBall(colors_of_balls_to_add[i], balls_to_add[i]);
    }
    for (const Coordinate coordinate : balls_to_remove) {
        removeBall(coordinate);
    }

    // Clears the data so the user cannot undo the undo.
    clearRecentMoveData();
}

void Board::clearRecentMoveData()
{
    m_newly_added_balls.clear();
    m_newly_removed_balls.clear();
    m_newly_removed_ball_colors.clear();
}

void Board::onSelectEmptyTile(const Coordinate move_to)
{
    if (m_move_from.has_value()) {
        getTile(*m_move_from)->ball()->stopAnimation();
        // Tries to move the ball.
        if (isValidMove(*m_move_from, move_to)) {
            // Clears earlier move data as a user starts a new valid move.
            clearRecentMoveData();
            moveBall(*m_move_from, move_to);
            m_move_from = std::nullopt;
            emit userTurnCompleted(move_to);
        } else {
            m_move_from = std::nullopt;
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
    // Uses BFS to check the existence of a path.
    const std::vector<Coordinate> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::queue<Coordinate> to_explore;
    QSet<Coordinate> visited;

    to_explore.push(move_from);
    visited.insert(move_from);

    while (!to_explore.empty()) {
        Coordinate current = to_explore.front();
        to_explore.pop();

        if (current == move_to) {
            return true;
        }

        for (const Coordinate &direction : directions) {
            const Coordinate next = current + direction;
            if (isEmptyTile(next) && !visited.contains(next)) {
                visited.insert(next);
                to_explore.push(next);
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
    const int random_index = QRandomGenerator::global()->bounded(list.size());
    return list.at(random_index);
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
