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
    void addBall(const QColor color, int x, int y);

private:
    QGraphicsScene *m_scene;
    int m_gridSize;
    // Array of pointers to Tile objects.
    Tile ***m_tiles;
    std::optional<Coordinate> m_move_from;

    // Renders an empty grid UI.
    void initializeTiles();

    void onSelectEmptyTile(Coordinate coordinate);
    void onSelectBall(Coordinate coordinate);
    void onUnselectBall();
    // Returns a pointer to the tile at coordinate.
    Tile *getTile(Coordinate coordinate);
};

#endif // BOARD_H
