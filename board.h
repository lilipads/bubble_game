#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include "QtWidgets/qwidget.h"

#include "ball.h"
#include "tile.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(int size, QWidget *parent = nullptr);
    QGraphicsScene *scene() const { return m_scene; }

    // Adds a ball to the given `coordinate` if and only if there is no ball there already. Throws an error if `coordinate` is out of range.
    void addBall(const BallColor color, const Coordinate coordinate);

    // Moves a ball from `from` to `to`. If no ball exists at `from`, nothing happens. Throws an error if either `from` or `to` is out of range.
    void moveBall(const Coordinate from, const Coordinate to);

    // Removes a ball at `coordinate`. If there is no ball, this is no-op. Throws an error if `coordinate` is out of range.
    void removeBall(const Coordinate coordinate);

    // Returns a random empty grid if it exists. Otherwise returns a nullopt.
    std::optional<Coordinate> getEmptyGrid();

signals:
    void userTurnCompleted(Coordinate coordinate);

private:
    QGraphicsScene *m_scene;
    int m_gridSize;
    // Array of pointers to Tile objects.
    Tile ***m_tiles;
    std::optional<Coordinate> m_move_from;
    // Keeps track of emtpy tiles.
    QSet<Coordinate> m_empty_tiles;

    // Renders an empty grid UI.
    void initializeTiles();
    // Moves the ball to the selected empty tile if there is a ball to move.
    void onSelectEmptyTile(const Coordinate move_to);
    void onSelectBall(const Coordinate move_from);
    void onUnselectBall();
    // Returns a pointer to the tile at coordinate if the coordinate is valid.
    // Throws an std::out_of_range error otherwise.
    Tile *getTile(const Coordinate coordinate);
    bool isValidMove(const Coordinate move_from, const Coordinate move_to);
};

#endif // BOARD_H
