#ifndef BALL_H
#define BALL_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QLinearGradient>

class Ball : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(qreal scaleY READ scaleY WRITE setScaleY NOTIFY scaleYChanged)
    Q_PROPERTY(qreal posY READ posY WRITE setPosY NOTIFY posYChanged)

public:
    Ball(const QColor color, const int size);
    QColor getColor() const { return m_color; };
    qreal scaleY() const { return transform().m22(); }
    void setScaleY(qreal scaleY);
    qreal posY() const { return pos().y(); };
    void setPosY(qreal posY);

signals:
    void scaleYChanged();
    void posYChanged();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int m_size;
    const QColor m_color;
    bool m_is_animating = false;

    // Generates the gradient to create a 3D-looking ball.
    QRadialGradient generateGradient(const QColor &baseColor) const;

    void animateBounce();
};

#endif // BALL_H
