#include "board.h"
#include <QGraphicsRectItem>
#include <QPen>

Board::Board(int size, QObject *parent)
    : QObject(parent)
    , m_scene(new QGraphicsScene(this))
    , m_gridSize(size)
{
    initializeBoard();
}

QGraphicsScene *Board::scene() const
{
    return m_scene;
}

void Board::initializeBoard()
{
    const QColor backgroundColor = Qt::gray;
    const QColor borderColor = Qt::darkGray;
    const int tileSize = 40;

    for (int i = 0; i < m_gridSize; ++i) {
        for (int j = 0; j < m_gridSize; ++j) {
            QGraphicsRectItem *tile = new QGraphicsRectItem(i * tileSize,
                                                            j * tileSize,
                                                            tileSize,
                                                            tileSize);
            tile->setBrush(backgroundColor);
            tile->setPen(QPen(borderColor));
            m_scene->addItem(tile);
        }
    }
}
