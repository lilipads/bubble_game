#include "ball.h"
#include <QBrush>
#include <QPainter>
#include <QPen>

Ball::Ball(const QColor color, const Tile *tile)
    : m_color(color)
    , m_coordinate(tile->coordinate())
    , m_topleft_x_pos(tile->coordinate().x * tile->size() + (tile->size() - kSize) / 2)
    , m_topleft_y_pos(tile->coordinate().y * tile->size() + (tile->size() - kSize) / 2)

{
    setAcceptHoverEvents(true);
    initializeAnimation();
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
    return QRectF(m_topleft_x_pos, m_topleft_y_pos, kSize, kSize);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRadialGradient gradient = generateGradient(m_color);
    painter->setBrush(QBrush(gradient));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(boundingRect());
}

QRadialGradient Ball::generateGradient(const QColor &baseColor) const
{
    const int r = baseColor.red();
    const int g = baseColor.green();
    const int b = baseColor.blue();

    const QColor brightShade(qMin(r + 240, 255), qMin(g + 240, 255), qMin(b + 240, 255));
    const QColor intermediateShade(qMin(r + 50, 255), qMin(g + 50, 255), qMin(b + 50, 255));
    const QColor darkShade(qMax(r - 155, 0), qMax(g - 155, 0), qMax(b - 155, 0));

    QRadialGradient gradient(/*cx=*/pos().x() + kSize / 2,
                             /*cy=*/pos().y() + kSize / 2,
                             /*radius=*/kSize / 2,
                             /*fx=*/kSize / 4,
                             /*fy=*/kSize / 4);
    gradient.setColorAt(0.0, brightShade);
    gradient.setColorAt(0.3, intermediateShade);
    gradient.setColorAt(0.7, darkShade);

    return gradient;
}

void Ball::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (!m_vertical_animation) {
            initializeAnimation();
        }
        if (m_vertical_animation->state() == QAbstractAnimation::Stopped) {
            startAnimation();
            emit onSelect(m_coordinate);
        } else {
            stopAnimation();
            emit onUnselect();
        }
    }
    QGraphicsObject::mousePressEvent(event);
}

void Ball::initializeAnimation()
{
    const qreal kSquashRatio = 0.8;
    const int kDuration = 1000;

    // Animation to squash the ball vertically.
    m_vertical_animation = new QPropertyAnimation(this, "scaleY");
    m_vertical_animation->setDuration(kDuration);
    m_vertical_animation->setStartValue(1.0);
    m_vertical_animation->setKeyValueAt(0.5, kSquashRatio); // Squash vertically at half duration
    m_vertical_animation->setEndValue(1.0);

    // Animation for shift down vertical position to keep bottom of the ball still.
    m_position_animation = new QPropertyAnimation(this, "posY");
    m_position_animation->setDuration(kDuration);
    m_position_animation->setStartValue(m_topleft_y_pos);
    m_position_animation->setKeyValueAt(0.5, m_topleft_y_pos + kSize * (1 - kSquashRatio));
    m_position_animation->setEndValue(m_topleft_y_pos);
}

void Ball::startAnimation()
{
    // Indefinite animation.
    m_vertical_animation->setLoopCount(-1);
    m_position_animation->setLoopCount(-1);

    m_vertical_animation->start();
    m_position_animation->start();
}

void Ball::stopAnimation()
{
    // Instead of using stop(), this brings the animation to an end.
    m_vertical_animation->setLoopCount(1);
    m_position_animation->setLoopCount(1);
}
