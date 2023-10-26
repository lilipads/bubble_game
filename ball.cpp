#include "ball.h"
#include <QBrush>
#include <QPainter>
#include <QPen>

Ball::Ball(const BallColor color, const int tile_size)
    : m_color(color)
    , m_margin_to_tile((tile_size - kSize) / 2)
{
    setAcceptHoverEvents(true);
    initializeAnimation();
}

QRectF Ball::boundingRect() const
{
    return QRectF(
        /*topLeft=*/QPointF(m_margin_to_tile, m_margin_to_tile), QSizeF(kSize, kSize));
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRadialGradient gradient = generateGradient(m_color);
    painter->setBrush(QBrush(gradient));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(boundingRect());
}

QRadialGradient Ball::generateGradient(const BallColor &base_color) const
{
    const QColor q_base_color = toQColor(base_color);

    QRadialGradient gradient(/*cx=*/kSize / 2,
                             /*cy=*/kSize / 2,
                             /*radius=*/kSize / 2,
                             /*fx=*/kSize / 4,
                             /*fy=*/kSize / 4);
    gradient.setColorAt(0.0, q_base_color.lighter());
    gradient.setColorAt(0.7, q_base_color);
    gradient.setColorAt(1.0, q_base_color.darker());

    return gradient;
}

void Ball::setScaleY(qreal scale_y)
{
    QTransform t = transform();

    // Squashes vertically.
    t.setMatrix(t.m11(), t.m12(), t.m13(), t.m21(), scale_y, t.m23(), t.m31(), t.m32(), t.m33());
    setTransform(t);

    // Shifts y to keeps the bottom position fixed.
    qreal pos_y = kSize * (1.0 - scale_y);
    setPos(pos().x(), pos_y);

    emit scaleYChanged();
}

bool Ball::isAnimating()
{
    return m_animation && m_animation->state() != QAbstractAnimation::Stopped;
}

void Ball::initializeAnimation()
{
    const qreal kSquashRatio = 0.7;
    const int kDuration = 800;

    // Animation to squash the ball vertically.
    m_animation = new QPropertyAnimation(this, "scaleY");
    m_animation->setDuration(kDuration);
    m_animation->setStartValue(1.0);
    // Squashes the ball vertically at half duration
    m_animation->setKeyValueAt(0.5, kSquashRatio);
    m_animation->setEndValue(1.0);
}

void Ball::startAnimation()
{
    if (!m_animation) {
        initializeAnimation();
    }
    // Indefinite animation.
    m_animation->setLoopCount(-1);
    m_animation->start();
}

void Ball::stopAnimation()
{
    if (!m_animation) {
        return;
    }
    m_animation->stop();
    setScaleY(1.0); // Restores ball to original shape.
}
