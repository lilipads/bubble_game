#include "Ball.h"

#include <QBrush>
#include <QLinearGradient>
#include <QPen>

Ball::Ball()
{
    QLinearGradient gradient(0, 0, 50, 50);
    gradient.setColorAt(0, Qt::red);
    gradient.setColorAt(1, Qt::gray);

    setBrush(QBrush(gradient));
    //    setPen(QPen(Qt::black, 2));
}
