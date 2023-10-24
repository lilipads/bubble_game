#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>
#include <QLinearGradient>

class Ball : public QGraphicsEllipseItem
{
public:
    Ball();

private:
    // Generates the gradient to create a 3D-looking ball.
    QRadialGradient generateGradient(const QColor &baseColor) const;
};

#endif // BALL_H
