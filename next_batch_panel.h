#ifndef NEXT_BATCH_PANEL_H
#define NEXT_BATCH_PANEL_H

#include <QGraphicsScene>
#include "QtWidgets/qwidget.h"

#include "ball.h"
#include "tile.h"

class NextBatchPanel : public QWidget
{
    Q_OBJECT

public:
    NextBatchPanel(int length, QWidget *parent = nullptr);
    QGraphicsScene *scene() const { return m_scene; }
    void updatePanel(const std::vector<BallColor> &colors);

private:
    QGraphicsScene *m_scene;
    // Array of pointers to Tile objects.
    Tile **m_tiles;
    int m_length;

    // Renders an empty grid UI.
    void initializeTiles();
};

#endif // NEXT_BATCH_PANEL_H
