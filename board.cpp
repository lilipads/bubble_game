#include "board.h"
#include <QGraphicsRectItem>
#include <QPen>

Board::Board(int size, QWidget *parent)
    : QWidget(parent)
    , m_scene(new QGraphicsScene(this))
    , m_gridSize(size)
{
    initializeBoardUi();
    initializeGrid();
    addBall(0, 0);
}

QGraphicsScene *Board::scene() const
{
    return m_scene;
}

void Board::initializeBoardUi()
{
    const QColor backgroundColor = Qt::gray;
    const QColor borderColor = Qt::darkGray;

    for (int x = 0; x < m_gridSize; ++x) {
        for (int y = 0; y < m_gridSize; ++y) {
            QGraphicsRectItem *tile = new QGraphicsRectItem(x * m_tileSize,
                                                            y * m_tileSize,
                                                            m_tileSize,
                                                            m_tileSize);
            tile->setBrush(backgroundColor);
            tile->setPen(QPen(borderColor));
            m_scene->addItem(tile);
        }
    }
}

void Board::initializeGrid()
{
    m_grid = new Ball **[m_gridSize];
    for (int x = 0; x < m_gridSize; ++x) {
        m_grid[x] = new Ball *[m_gridSize];
        for (int y = 0; y < m_gridSize; ++y) {
            m_grid[x][y] = nullptr;
        }
    }
}

void Board::addBall(int x, int y)
{
    if (!(x >= 0 && x < m_gridSize && y >= 0 && y < m_gridSize)) {
        return;
    }
    if (!m_grid[x][y]) { // Check if there's no ball already at the position
        m_grid[x][y] = new Ball();
        m_grid[x][y]->setRect(x * m_tileSize + (m_tileSize - m_ballSize) / 2,
                              y * m_tileSize + (m_tileSize - m_ballSize) / 2,
                              m_ballSize,
                              m_ballSize);
        m_scene->addItem(m_grid[x][y]);
    }
}
