#ifndef COORDINATE_H
#define COORDINATE_H

#include <QHash>
#include <QString>

struct Coordinate
{
    int x;
    int y;

    QString toString() const { return QString("(%1, %2)").arg(x).arg(y); }

    bool operator==(const Coordinate &other) const { return x == other.x && y == other.y; }

    Coordinate &operator+=(const Coordinate &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
};

inline uint qHash(const Coordinate &key, uint seed = 0)
{
    return qHash(key.x, seed) ^ qHash(key.y, seed);
}

#endif // COORDINATE_H
