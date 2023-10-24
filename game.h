#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    QGraphicsScene *gameScene() const;

private:
    const int kGridSize = 9;

    Board *m_board;
};

#endif // GAME_H
