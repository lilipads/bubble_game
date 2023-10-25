#include "ball.h"
#include <QBrush>
#include <QPainter>
#include <QPen>

Ball::Ball(const BallColor color, const int tileSize)
    : m_color(color)
    , m_margin_to_tile((tileSize - kSize) / 2)
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

QRadialGradient Ball::generateGradient(const BallColor &baseColor) const
{
    const QColor qBaseColor = toQColor(baseColor);
    const int r = qBaseColor.red();
    const int g = qBaseColor.green();
    const int b = qBaseColor.blue();

    const QColor brightShade(qMin(r + 240, 255), qMin(g + 240, 255), qMin(b + 240, 255));
    const QColor intermediateShade(qMin(r + 50, 255), qMin(g + 50, 255), qMin(b + 50, 255));
    const QColor darkShade(qMax(r - 155, 0), qMax(g - 155, 0), qMax(b - 155, 0));

    QRadialGradient gradient(/*cx=*/kSize / 2,
                             /*cy=*/kSize / 2,
                             /*radius=*/kSize / 2,
                             /*fx=*/kSize / 4,
                             /*fy=*/kSize / 4);
    gradient.setColorAt(0.0, brightShade);
    gradient.setColorAt(0.5, intermediateShade);
    gradient.setColorAt(0.9, darkShade);

    return gradient;
}

void Ball::setScaleY(qreal scaleY)
{
    QTransform t = transform();

    // Squashes vertically.
    t.setMatrix(t.m11(), t.m12(), t.m13(), t.m21(), scaleY, t.m23(), t.m31(), t.m32(), t.m33());
    setTransform(t);

    // Shifts y to keeps the bottom position fixed.
    qreal posYOffset = kSize * (1.0 - scaleY);
    setPos(pos().x(), posYOffset);

    emit scaleYChanged();
}

bool Ball::isAnimating()
{
    return m_animation && m_animation->state() != QAbstractAnimation::Stopped;
}

void Ball::initializeAnimation()
{
    const qreal kSquashRatio = 0.8;
    const int kDuration = 1000;

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
