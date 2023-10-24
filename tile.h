#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include "coordinate.h"

class Tile : public QGraphicsObject
{
    Q_OBJECT

public:
    Tile(Coordinate p);
    int size() const { return kSize; }
    Coordinate coordinate() const { return m_coordinate; }

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

signals:
    void onClick(Coordinate coordinate);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    static const int kSize = 40;
    const QColor kBackgroundColor = Qt::gray;
    const QColor kBorderColor = Qt::darkGray;

    Coordinate m_coordinate;
};

#endif // TILE_H
