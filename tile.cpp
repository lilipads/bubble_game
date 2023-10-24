#include "tile.h"

#include <QPen>

Tile::Tile(Position p)
    : m_position(p)
    , QGraphicsRectItem(p.x * kSize, p.y * kSize, kSize, kSize)
{
    setBrush(kBackgroundColor);
    setPen(QPen(kBorderColor));
}
