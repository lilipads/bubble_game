#ifndef BALL_H
#define BALL_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QLinearGradient>
#include "tile.h"

class Ball : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(qreal scaleY READ scaleY WRITE setScaleY NOTIFY scaleYChanged)
    Q_PROPERTY(qreal posY READ posY WRITE setPosY NOTIFY posYChanged)

public:
    Ball(const QColor color, const Tile *tile);
    QColor color() const { return m_color; };
    Position position() const { return m_position; }

    qreal scaleY() const { return transform().m22(); }
    void setScaleY(qreal scaleY);
    qreal posY() const { return pos().y(); };
    void setPosY(qreal posY);

signals:
    void scaleYChanged();
    void posYChanged();
    void onClick(Position position);

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    static const int kSize = 30;
    Position m_position;
    const QColor m_color;
    bool m_is_animating = false;

    // Generates the gradient to create a 3D-looking ball.
    QRadialGradient generateGradient(const QColor &baseColor) const;

    void animateBounce();
};

#endif // BALL_H
