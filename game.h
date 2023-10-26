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

signals:
    void scoreUpdated(int score);

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

    // Updates m_score and eliminates lines if any line is formed at the
    // `coordinate`. Otherwise, adds a new ball to the board.
    void scoreAndUpdateBoard(const Coordinate coordinate);

    void setAndDisplayNextBatchColors();

    // Randomly samples colors with replacement.
    std::vector<BallColor> getNextBatchColors() const;

    // Adds up to kNewBalls balls when there is still space, and updates the
    // display panel for the next batch of balls.
    void addNewBalls();

    // Returns incremental score for lines formed in any direction containing
    // `coordinate`. Removes such lines if they reach the minimal length to
    // score.
    int getDeltaScoreAndRemoveLines(const Coordinate coordinate);

    // Scores a line containing the `origin` in `direction` and its opposite
    // direction, (e.g. `direction` = (0, 1) means the vertical direction, both
    // up and down). If the line has a score, updates `delta_score` and removes
    // the line except `origin` from the board.
    void scoreLineAndRemoveSegments(const Coordinate origin,
                                    const Coordinate direction,
                                    const int per_ball_score,
                                    int &delta_score);

    // Returns coordinates of consecutive tiles with balls of the same color as
    // that of the ball at `origin` in a given `direction` if they exist. This
    // does not include the Tile at the `origin`.
    std::vector<Coordinate> getConsecutiveCoordWithSameColor(const Coordinate origin,
                                                             const Coordinate direction) const;

    // Returns the score of the line. Can be 0 if the line doesn't qualify.
    // `segment1` and `segment2`, together with the origin (the spacing in
    // between the two segments), join togehter to form a consecutive line.
    int scoreLine(const std::vector<Coordinate> &segment1,
                  const std::vector<Coordinate> &segment2,
                  const int per_ball_score) const;

    // Removes balls from `segment1` and `segment2`.
    void removeSegments(const std::vector<Coordinate> &segment1,
                        const std::vector<Coordinate> &segment2);
};

#endif // GAME_H
