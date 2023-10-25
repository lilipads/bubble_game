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
    QGraphicsScene *scene() const;

    // Adds a ball to the given location if and only if the location is valid
    // and there is no ball there already.
    void addBall(const QColor color, const Coordinate coordinate);

    // Moves a ball from `from` to `to`. If no ball exists at `from`, nothing happens.
    void moveBall(const Coordinate from, const Coordinate to);

private:
    QGraphicsScene *m_scene;
    int m_gridSize;
    // Array of pointers to Tile objects.
    Tile ***m_tiles;
    std::optional<Coordinate> m_move_from;

    // Renders an empty grid UI.
    void initializeTiles();
    // Moves the ball to the selected empty tile if there is a ball to move.
    void onSelectEmptyTile(Coordinate move_to);
    void onSelectBall(Coordinate move_from);
    void onUnselectBall();
    // Returns a pointer to the tile at coordinate if the coordinate is valid.
    // Throws an std::out_of_range error otherwise.
    Tile *getTile(Coordinate coordinate);
};

#endif // BOARD_H
