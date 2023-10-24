#ifndef GAME_H
#define GAME_H

#include <QObject>
#include "board.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    QGraphicsScene *gameScene() const;

private:
    const int gridSize = 9;

    Board *m_board;
};

#endif // GAME_H
