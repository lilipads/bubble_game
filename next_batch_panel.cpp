#include "next_batch_panel.h"

NextBatchPanel::NextBatchPanel(int length, QWidget *parent)
    : QWidget(parent)
    , m_scene(new QGraphicsScene(this))
    , m_length(length)
{
    initializeTiles();
}

void NextBatchPanel::initializeTiles()
{
    m_tiles = new Tile *[m_length];
    const int y = 0;
    for (int x = 0; x < m_length; ++x) {
        Tile *tile = new Tile({.x = x, .y = y});
        tile->setPos(x * tile->size(), y * tile->size());
        m_tiles[x] = tile;
        m_scene->addItem(tile);
    }
}

void NextBatchPanel::updatePanel(const std::vector<BallColor> &colors)
{
    for (int x = 0; x < m_length && x < colors.size(); ++x) {
        Tile *tile = m_tiles[x];
        Ball *ball = new Ball(colors[x], tile->size());
        tile->removeBall();
        tile->setBall(ball);
    }
}
