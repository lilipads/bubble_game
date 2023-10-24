#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include "position.h"

class Tile : public QGraphicsObject
{
    Q_OBJECT

public:
    Tile(Position p);
    int size() const { return kSize; }
    Position position() const { return m_position; }

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

signals:
    void onClick(Tile* tile);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    static const int kSize = 40;
    const QColor kBackgroundColor = Qt::gray;
    const QColor kBorderColor = Qt::darkGray;

    Position m_position;
};

#endif // TILE_H
