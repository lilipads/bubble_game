#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "next_batch_panel.h"

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    QGraphicsScene *boardScene() const;
    QGraphicsScene *panelScene() const;

    void startGame();

    int getScore() const { return m_score; }

private:
    const int kGridSize = 9;
    const int kNewBalls = 3;
    // Needs at least 5 balls in a row to score a line.
    const int kMinLine = 5;
    const int kNonDiagLineScore = 2;
    const int kDiagLineScore = 3;

    Board *m_board;
    NextBatchPanel *m_panel;
    int m_score;
    std::vector<BallColor> m_next_batch_colors;

    // Updates m_score and eliminates lines if any line is formed at the `coordinate`. Otherwise, adds new ball to the board.
    void scoreAndUpdateBoard(const Coordinate coordinate);

    void setAndDisplayNextBatchColors();

    // Randomly samples colors with replacement.
    std::vector<BallColor> getNextBatchColors() const;

    // Adds up to kNewBalls balls when there is still space, and update the display panel for the next batch of balls.-
    void addNewBalls();

    // Returns incremental score for lines formed in any direction containing `coordinate`. Removes such lines if they reach the minimal length to score.
    int getDeltaScoreAndEliminateLines(const Coordinate coordinate);

    // `direction` is a unit vector such as (0, 1). Scores a line containing the `origin` in `direction` and its opposite direction, (e.g. (0, 1) means the vertical direction). If the line has a score, update `delta_score` and removes the line except `origin` from the board.
    void scoreLineAndRemoveSegments(const Coordinate origin,
                                    const Coordinate direction,
                                    const int per_ball_score,
                                    int &delta_score);

    //  Returns coordinates of consecutive tiles with the same color ball as the ball at `origin` in a given `direction` if they exist. This does not include the Tile at the `origin`.
    std::vector<Coordinate> getConsecutiveCoordWithSameColor(const Coordinate origin,
                                                             const Coordinate direction) const;

    // Returns the score of the line. Can be 0 if the line doesn't qualify. `segment1` and `segment2`, together with the origin (the spacing in between the two segments), joins togehter to form a consecutive line.
    int scoreLine(const std::vector<Coordinate> &segment1,
                  const std::vector<Coordinate> &segment2,
                  const int per_ball_score) const;

    // Removes balls from `segment1` and `segment2`.
    void removeSegments(const std::vector<Coordinate> &segment1,
                        const std::vector<Coordinate> &segment2);
};

#endif // GAME_H
