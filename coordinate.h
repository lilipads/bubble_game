#ifndef COORDINATE_H
#define COORDINATE_H

#include <QString>

struct Coordinate
{
    int x;
    int y;

    QString toString() const { return QString("(%1, %2)").arg(x).arg(y); }
};

#endif // COORDINATE_H
