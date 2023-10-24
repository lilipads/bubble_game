#include "ball.h"
#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QPropertyAnimation>

Ball::Ball(const QColor color, const Tile *tile)
    : m_color(color)
    , m_position(tile->position())
{
    setAcceptHoverEvents(true);
    setPos(tile->pos().x() + (tile->size() - kSize) / 2,
           tile->pos().y() + (tile->size() - kSize) / 2);
}

void Ball::setScaleY(qreal scaleY)
{
    QTransform t = transform();
    t.setMatrix(t.m11(), t.m12(), t.m13(), t.m21(), scaleY, t.m23(), t.m31(), t.m32(), t.m33());
    setTransform(t);
    emit scaleYChanged();
}

void Ball::setPosY(qreal posY)
{
    setPos(pos().x(), posY);
    emit posYChanged();
}

QRectF Ball::boundingRect() const
{
    return QRectF(0, 0, kSize, kSize);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRadialGradient gradient = generateGradient(m_color);
    painter->setBrush(QBrush(gradient));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(boundingRect());
}

void Ball::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_is_animating) {
        return;
    }
    if (event->button() == Qt::LeftButton) {
        animateBounce();
        m_is_animating = true;
    }
    emit onClick(m_position);
    QGraphicsObject::mousePressEvent(event);
}

QRadialGradient Ball::generateGradient(const QColor &baseColor) const
{
    int r = baseColor.red();
    int g = baseColor.green();
    int b = baseColor.blue();

    QColor brightShade(qMin(r + 240, 255), qMin(g + 240, 255), qMin(b + 240, 255));
    QColor intermediateShade(qMin(r + 50, 255), qMin(g + 50, 255), qMin(b + 50, 255));
    QColor darkShade(qMax(r - 155, 0), qMax(g - 155, 0), qMax(b - 155, 0));

    QRadialGradient gradient(kSize / 2, kSize / 2, kSize / 2, kSize / 4, kSize / 4);
    gradient.setColorAt(0.0, brightShade);
    gradient.setColorAt(0.3, intermediateShade);
    gradient.setColorAt(0.7, darkShade);

    return gradient;
}

void Ball::animateBounce()
{
    const qreal kSquashRatio = 0.8;
    QPropertyAnimation *verticalAnimation = new QPropertyAnimation(this, "scaleY");
    verticalAnimation->setDuration(1000);
    verticalAnimation->setStartValue(1.0);
    verticalAnimation->setKeyValueAt(0.5, kSquashRatio); // Squash vertically at half duration
    verticalAnimation->setEndValue(1.0);
    verticalAnimation->setLoopCount(-1); // Indefinite animation

    // Animation for vertical position to keep bottom y position unchanged
    QPropertyAnimation *positionAnimation = new QPropertyAnimation(this, "posY");
    qreal originalY = posY();
    positionAnimation->setDuration(1000);
    positionAnimation->setStartValue(originalY);
    positionAnimation->setKeyValueAt(0.5, originalY + kSize * (1 - kSquashRatio));
    positionAnimation->setEndValue(originalY);
    positionAnimation->setLoopCount(-1);

    verticalAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    positionAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}
