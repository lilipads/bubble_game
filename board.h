#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include <QObject>

class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(int size, QObject *parent = nullptr); // Accept gridSize as a parameter
    QGraphicsScene *scene() const;

private:
    QGraphicsScene *m_scene;
    int m_gridSize;
    void initializeBoard();
};

#endif // BOARD_H
