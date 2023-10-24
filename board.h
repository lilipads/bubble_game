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
    // Array of pointers to Ball objects. TODO: delete this. Make ball a member of Tile.
    Ball ***m_ball_tracker;

    // Renders an empty grid UI.
    void initializeTiles();

    // Initializes all pointers to nullptr.
    void initializeBallTracker();

    void handleTileClick(Tile *clickedTile)
    {
        // Implement what you want to do when a tile is clicked here
        qDebug() << "Tile clicked at position:" << clickedTile->position().x
                 << clickedTile->position().y;
    }
};

#endif // BOARD_H
