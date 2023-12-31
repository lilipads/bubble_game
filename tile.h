#ifndef TILE_H
#define TILE_H

#include <QGraphicsRectItem>
#include "ball.h"
#include "coordinate.h"

class Tile : public QGraphicsObject
{
    Q_OBJECT

public:
    Tile(Coordinate c);
    int size() const { return kSize; }
    Coordinate coordinate() const { return m_coordinate; }
    void setBall(Ball* ball);
    // Removes the ball from the tile. If no ball exists, this is a no-op.
    void removeBall();
    Ball* ball() const { return m_ball; }
    bool hasBall() const { return m_ball != nullptr; }

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

signals:
    void selectEmptyTile(Coordinate coordinate);
    void unselectBall();
    void selectBall(Coordinate coordinate);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    static const int kSize = 40;
    const QColor kBackgroundColor = Qt::gray;
    const QColor kBorderColor = Qt::darkGray;

    Coordinate m_coordinate;
    Ball* m_ball = nullptr;
};

#endif // TILE_H
