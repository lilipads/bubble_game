#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>
#include "QtWidgets/qwidget.h"

#include "ball.h"
#include "tile.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    explicit Board(int size, QWidget *parent = nullptr);
    QGraphicsScene *scene() const { return m_scene; }

    // Adds a ball to the given `coordinate` if and only if there is no ball
    // there already. Throws an error if `coordinate` is out of range.
    void addBall(const BallColor color, const Coordinate coordinate);

    // Moves a ball from `from` to `to`. If no ball exists at `from`, nothing
    // happens. Throws an error if either `from` or `to` is out of range.
    void moveBall(const Coordinate from, const Coordinate to);

    // Removes a ball at `coordinate`. If there is no ball, this is no-op.
    // Throws an error if `coordinate` is out of range.
    void removeBall(const Coordinate coordinate);

    // Returns a random empty grid if it exists. Otherwise returns a nullopt.
    std::optional<Coordinate> getRandomEmptyGrid();

    // Returns the ball color if a ball exists at `coordinate`. Returns
    // nullopt if no ball exists at `coordinate` or if `coordinate` is out
    // of range.
    std::optional<BallColor> getBallColor(Coordinate coordinate);

    // Undoes the most recent move.
    void undo();

signals:
    void userTurnCompleted(Coordinate coordinate);

private:
    QGraphicsScene *m_scene;
    int m_gridSize;
    // Array of pointers to Tile objects.
    Tile ***m_tiles;
    std::optional<Coordinate> m_move_from;
    // Keeps track of emtpy tiles.
    QSet<Coordinate> m_empty_tiles;
    std::vector<Coordinate> m_newly_added_balls;
    std::vector<Coordinate> m_newly_removed_balls;
    std::vector<BallColor> m_newly_removed_ball_colors;

    // Renders an empty grid UI.
    void initializeTiles();

    // Moves the ball to the selected empty tile at `move_to` if there is a ball
    // to move.
    void onSelectEmptyTile(const Coordinate move_to);

    // Updates `m_move_from` to prepare to move the selected ball. If another
    // ball is being selected, stop animating that ball. Throws an error if
    // `move_from` is out of range.
    void onSelectBall(const Coordinate move_from);

    // Updates `m_move_from` to erase the previous selected coordinate.
    void onUnselectBall();

    // Returns a pointer to the tile at coordinate if the coordinate is valid.
    // Throws an std::out_of_range error otherwise.
    Tile *getTile(const Coordinate coordinate);

    // Returns true if there is a path between `move_from` and `move_to`.
    // A path means the ball can move up / down / left / right across empty tiles
    // from the source to the destination.
    bool isValidMove(const Coordinate move_from, const Coordinate move_to);

    // Returns true if it is an empty tile. Returns false if the tile has a ball
    // or if the coordinate is not valid.
    bool isEmptyTile(const Coordinate coordinate) const;

    // Clears the data on the recent move to disallow an undo.
    void clearRecentMoveData();
};

#endif // BOARD_H
