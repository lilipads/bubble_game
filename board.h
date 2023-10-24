#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include "QtWidgets/qwidget.h"
#include "ball.h"

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
    const int m_tileSize = 40;
    const int m_ballSize = 30;
    // array to track ball placement with pointers to Ball objects.
    Ball ***m_grid;

    // Renders an empty grid UI.
    void initializeBoardUi();

    // Initialize all pointers to nullptr.
    void initializeGrid();
};

#endif // BOARD_H
