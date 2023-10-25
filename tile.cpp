#include "tile.h"
#include "ball.h"

#include <QPainter>
#include <QPen>

Tile::Tile(Coordinate p)
    : m_coordinate(p)
{}

QRectF Tile::boundingRect() const
{
    return QRectF(0, 0, kSize, kSize);
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

void Tile::setBall(Ball* ball)
{
    // Don't do anything if there is an existing ball.
    if (m_ball) {
        return;
    }
    m_ball = ball;
    ball->setParentItem(this);
    ball->setPos(0, 0);
}
