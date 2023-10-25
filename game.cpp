#include "game.h"

#include <random>

Game::Game(QWidget *parent)
    : QWidget(parent)
    , m_board(new Board(kGridSize, this)) // Initialize Board instance
{}

QGraphicsScene *Game::gameScene() const
{
    return m_board->scene();
}

void Game::scoreAndUpdateBoard(const Coordinate coordinate)
{
    const int delta_score = getDeltaScoreAndEliminateLines(coordinate);
    m_score += delta_score;
    if (delta_score == 0) {
        addNewBalls();
    }
}

int Game::getDeltaScoreAndEliminateLines(const Coordinate coordinate)
{
    const int delta_score = 0;
    // Horizontal.
    // Vertical.
    // Forward slash.
    // Backward slach.
    if (delta_score > 0) {
        // Removes the origin.
    }
    return delta_score;
}

void Game::addNewBalls()
{
    for (int i = 0; i < m_next_batch_colors.size(); ++i) {
        std::optional<Coordinate> coordinate_or = m_board->getEmptyGrid();
        if (coordinate_or.has_value()) {
            m_board->addBall(m_next_batch_colors[i], *coordinate_or);
        }
    }
    setAndDisplayNextBatchColors();
}

std::vector<BallColor> Game::getNextBatchColors()
{
    static std::random_device rd;  // Used to initialize our mersenne_twister_engine
    static std::mt19937 gen(rd()); // A mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, kNumColors - 1);

    std::vector<BallColor> sampledColors;
    for (int i = 0; i < kNewBalls; ++i) {
        BallColor color = static_cast<BallColor>(distrib(gen));
        sampledColors.push_back(color);
    }

    return sampledColors;
}

void Game::setAndDisplayNextBatchColors()
{
    m_next_batch_colors = getNextBatchColors();
    // TODO: display next batch colors
}
