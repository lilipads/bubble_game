#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include "position.h"

class Tile : public QGraphicsRectItem
{
public:
    Tile(Position p);
    int size() const { return kSize; }
    Position position() const { return m_position; }

private:
    static const int kSize = 40;
    const QColor kBackgroundColor = Qt::gray;
    const QColor kBorderColor = Qt::darkGray;

    Position m_position;
};

#endif // TILE_H
