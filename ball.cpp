#include "Ball.h"

#include <QBrush>

#include <QPen>

Ball::Ball()
{
    QRadialGradient gradient = generateGradient(Qt::blue);
    setBrush(QBrush(gradient));
    setPen(Qt::NoPen);
}

QRadialGradient Ball::generateGradient(const QColor &baseColor) const
{
    int r = baseColor.red();
    int g = baseColor.green();
    int b = baseColor.blue();

    // Compute the bright, intermediate, and dark shades
    QColor brightShade(qMin(r + 240, 255), qMin(g + 240, 255), qMin(b + 240, 255));
    QColor intermediateShade(qMin(r + 50, 255), qMin(g + 50, 255), qMin(b + 50, 255));
    QColor darkShade(qMax(r - 155, 0), qMax(g - 155, 0), qMax(b - 155, 0));

    QRadialGradient gradient(25, 25, 30, 15, 15);
    gradient.setColorAt(0.0, brightShade);
    gradient.setColorAt(0.3, intermediateShade);
    gradient.setColorAt(0.7, darkShade);

    return gradient;
}
