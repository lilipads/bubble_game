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

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    const QRectF rect = boundingRect();

    const QColor tile_color(200, 200, 200);
    const QColor light_shade = Qt::white; // Lighter shade for top and left
    const QColor dark_shade = Qt::black;  // Darker shade for bottom and right
    const qreal gradient_width = 4.0;

    painter->fillRect(rect, tile_color);

    // Top gradient (light_shade to tile_color)
    QLinearGradient top_gradient(rect.topLeft(), rect.topLeft() + QPointF(0, gradient_width));
    top_gradient.setColorAt(0, light_shade);
    top_gradient.setColorAt(1, tile_color);
    painter->fillRect(QRectF(rect.topLeft(), rect.topRight() + QPointF(0, gradient_width)),
                      top_gradient);

    // Left gradient (light_shade to tile_color)
    QLinearGradient left_gradient(rect.topLeft(), rect.topLeft() + QPointF(gradient_width, 0));
    left_gradient.setColorAt(0, light_shade);
    left_gradient.setColorAt(1, tile_color);
    painter->fillRect(QRectF(rect.topLeft(), rect.bottomLeft() + QPointF(gradient_width, 0)),
                      left_gradient);

    // Bottom gradient (tile_color to dark_shade)
    QLinearGradient bottom_gradient(rect.bottomLeft() - QPointF(0, gradient_width),
                                    rect.bottomLeft());
    bottom_gradient.setColorAt(0, tile_color);
    bottom_gradient.setColorAt(1, dark_shade);
    painter->fillRect(QRectF(rect.bottomLeft() - QPointF(0, gradient_width), rect.bottomRight()),
                      bottom_gradient);

    // Right gradient (tile_color to dark_shade)
    QLinearGradient right_gradient(rect.topRight() - QPointF(gradient_width, 0), rect.topRight());
    right_gradient.setColorAt(0, tile_color);
    right_gradient.setColorAt(1, dark_shade);
    painter->fillRect(QRectF(rect.topRight() - QPointF(gradient_width, 0),
                             rect.bottomRight() - QPointF(0, gradient_width)),
                      right_gradient);
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

void Tile::setBall(Ball *ball)
{
    // Don't do anything if there is an existing ball.
    if (m_ball) {
        return;
    }
    m_ball = ball;
    ball->setParentItem(this);
    ball->setPos(0.0, 0.0);
}

void Tile::removeBall()
{
    if (m_ball != nullptr) {
        delete m_ball;
        m_ball = nullptr;
    }
}
