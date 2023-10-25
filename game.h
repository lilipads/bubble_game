#ifndef GAME_H
#define GAME_H

#include "board.h"

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    QGraphicsScene *gameScene() const;

    // Updates m_score and eliminates line if any line is formed at the `coordinate`.
    void scoreAndUpdateBoard(const Coordinate coordinate);
    int getScore() { return m_score; }

private:
    const int kGridSize = 9;
    const int kNewBalls = 3;
    Board *m_board;
    int m_score;
    std::vector<BallColor> m_next_batch_colors;

    void setAndDisplayNextBatchColors();
    // Randomly samples colors with replacement.
    std::vector<BallColor> getNextBatchColors();
    // Adds up to kNewBalls balls when there is still space.
    void addNewBalls();
    int getDeltaScoreAndEliminateLines(const Coordinate coordinate);

    //  Returns pointers to consecutive consecutive tiles with the same color ball as the ball at `origin` if exists in a given `direction`. This does not include the Tile at the `origin`.
    std::vector<Tile *> getConsecutiveTilesWithSameColorBalls(const Coordinate origin,
                                                              const Coordinate direction);
};

#endif // GAME_H
