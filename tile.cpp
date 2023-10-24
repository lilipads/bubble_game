#include "tile.h"

#include <QPainter>
#include <QPen>

Tile::Tile(Position p)
    : m_position(p)
{}

QRectF Tile::boundingRect() const
{
    return QRectF(m_position.x * kSize, m_position.y * kSize, kSize, kSize);
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
    emit onClick(m_position);
    QGraphicsObject::mousePressEvent(event);
}
