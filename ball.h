#ifndef BALL_H
#define BALL_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QLinearGradient>
#include <QPropertyAnimation>
#include "coordinate.h"

class Ball : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(qreal scaleY READ scaleY WRITE setScaleY NOTIFY scaleYChanged)

public:
    Ball(const QColor color, const int tileSize);
    QColor color() const { return m_color; };

    qreal scaleY() const { return transform().m22(); }
    void setScaleY(qreal scaleY);

signals:
    void scaleYChanged();
    void onSelect(Coordinate coordinate);
    void onUnselect();

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static const int kSize = 30;
    const qreal m_margin_to_tile;

    const QColor m_color;
    QPropertyAnimation *m_animation;

    // Generates the gradient to create a 3D-looking ball.
    QRadialGradient generateGradient(const QColor &baseColor) const;

    // Animation for bounce effect.
    void initializeAnimation();
    void startAnimation();
    void stopAnimation();
};

#endif // BALL_H
