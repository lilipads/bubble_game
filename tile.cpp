#include "tile.h"

#include <QPainter>
#include <QPen>

Tile::Tile(Coordinate p)
    : m_coordinate(p)
{}

QRectF Tile::boundingRect() const
{
    return QRectF(m_coordinate.x * kSize, m_coordinate.y * kSize, kSize, kSize);
}

void Tile::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(kBackgroundColor);
    painter->setPen(QPen(kBorderColor));
    painter->drawRect(boundingRect());
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit onClick(m_coordinate);
    QGraphicsObject::mousePressEvent(event);
}
