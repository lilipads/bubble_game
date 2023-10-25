#include "tile.h"
#include "ball.h"

#include <QPainter>
#include <QPen>

Tile::Tile(Coordinate p)
    : m_coordinate(p)
{}

QRectF Tile::boundingRect() const
{
    return QRectF(/*topLeft=*/QPointF(0.0, 0.0), QSizeF(kSize, kSize));
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
    if (m_ball) {
        if (m_ball->isAnimating()) {
            m_ball->stopAnimation();
            emit unselectBall();
        } else {
            m_ball->startAnimation();
            emit selectBall(m_coordinate);
        }
    } else {
        emit selectEmptyTile(m_coordinate);
    }
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
    ball->setPos(0.0, 0.0);
}
