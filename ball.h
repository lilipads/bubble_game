#ifndef BALL_H
#define BALL_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QLinearGradient>
#include <QPropertyAnimation>

const int kNumColors = 6;
enum class BallColor { Red, Yellow, Brown, Green, Blue, White };

inline QColor toQColor(const BallColor &color)
{
    switch (color) {
    case BallColor::Red:
        return Qt::red;
    case BallColor::Yellow:
        return Qt::yellow;
    case BallColor::Brown:
        return QColor(165, 42, 42);
    case BallColor::Green:
        return Qt::green;
    case BallColor::Blue:
        return Qt::blue;
    case BallColor::White:
        return Qt::white;
    default:
        throw std::invalid_argument("Unsupported color!");
    }
}

class Ball : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(qreal scaleY READ scaleY WRITE setScaleY NOTIFY scaleYChanged)

public:
    Ball(const BallColor color, const int tileSize);
    BallColor color() const { return m_color; };

    // Animation for bounce effect.
    void startAnimation();
    void stopAnimation();
    bool isAnimating();
    qreal scaleY() const { return transform().m22(); }
    void setScaleY(qreal scale_y);

signals:
    void scaleYChanged();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    static const int kSize = 30;
    const qreal m_margin_to_tile;

    const BallColor m_color;
    QPropertyAnimation *m_animation;

    // Generates the gradient to create a 3D-looking ball.
    QRadialGradient generateGradient(const BallColor &baseColor) const;

    void initializeAnimation();
};

#endif // BALL_H
