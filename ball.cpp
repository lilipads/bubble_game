#include "Ball.h"

#include <QBrush>
#include <QLinearGradient>
#include <QPen>

Ball::Ball()
{
    QRadialGradient gradient(25, 25, 30, 15, 15);

    gradient.setColorAt(0.0, QColor(255, 240, 240));
    gradient.setColorAt(0.3, QColor(255, 50, 50));
    gradient.setColorAt(0.7, QColor(100, 0, 0));

    setBrush(QBrush(gradient));
    setPen(Qt::NoPen);
}
