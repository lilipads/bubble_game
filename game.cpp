#include "game.h"

#include <random>

Game::Game(QWidget *parent)
    : QWidget(parent)
    , m_board(new Board(kGridSize, this))
    , m_panel(new NextBatchPanel(kNewBalls, this))
{
    connect(m_board, &Board::userTurnCompleted, this, &Game::scoreAndUpdateBoard);
    addNewBalls();
}

QGraphicsScene *Game::boardScene() const
{
    return m_board->scene();
}

QGraphicsScene *Game::panelScene() const
{
    return m_panel->scene();
}

void Game::scoreAndUpdateBoard(const Coordinate coordinate)
{
    const int delta_score = getDeltaScoreAndRemoveLines(coordinate);
    m_score += delta_score;
    if (delta_score == 0) {
        addNewBalls();
    }
    emit scoreUpdated(m_score);
}

int Game::getDeltaScoreAndRemoveLines(const Coordinate coordinate)
{
    int delta_score = 0;
    // Horizontal.
    scoreLineAndRemoveSegments(coordinate, {.x = 1, .y = 0}, kNonDiagLineScore, delta_score);

    // Vertical.
    scoreLineAndRemoveSegments(coordinate, {.x = 0, .y = 1}, kNonDiagLineScore, delta_score);

    // Forward slash.
    scoreLineAndRemoveSegments(coordinate, {.x = 1, .y = 1}, kDiagLineScore, delta_score);

    // Backward slash.
    scoreLineAndRemoveSegments(coordinate, {.x = 1, .y = -1}, kNonDiagLineScore, delta_score);

    if (delta_score > 0) {
        // Removes the origin.
        m_board->removeBall(coordinate);
    }
    return delta_score;
}

void Game::scoreLineAndRemoveSegments(const Coordinate origin,
                                      const Coordinate direction,
                                      const int per_ball_score,
                                      int &delta_score)
{
    const auto segment1 = getSegmentWithSameColor(origin, direction);
    const auto segment2 = getSegmentWithSameColor(origin, -direction);
    const int score = scoreLine(segment1, segment2, per_ball_score);
    if (score > 0) {
        removeSegments(segment1, segment2);
    }
    delta_score += score;
}

void Game::addNewBalls()
{
    if (m_next_batch_colors.size() == 0) {
        setAndDisplayNextBatchColors();
    }
    for (int i = 0; i < m_next_batch_colors.size(); ++i) {
        std::optional<Coordinate> coordinate_or = m_board->getRandomEmptyGrid();
        if (coordinate_or.has_value()) {
            m_board->addBall(m_next_batch_colors[i], *coordinate_or);
            // A newly placed ball can form a qualifying line (e.g. if there are already 4
            // consecutive balls, and a new ball is added to the end of the line).
            // Also adds that to the score.
            m_score += getDeltaScoreAndRemoveLines(*coordinate_or);
        }
    }
    setAndDisplayNextBatchColors();
}

std::vector<BallColor> Game::getNextBatchColors() const
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
    m_panel->updatePanel(m_next_batch_colors);
}

std::vector<Coordinate> Game::getSegmentWithSameColor(const Coordinate origin,
                                                      const Coordinate direction) const
{
    std::vector<Coordinate> tiles;
    const std::optional<BallColor> origin_color_or = m_board->getBallColor(origin);
    if (!origin_color_or.has_value()) {
        return tiles;
    }
    const BallColor origin_color = *origin_color_or;

    Coordinate curr = origin;
    while (true) {
        curr += direction;
        const std::optional<BallColor> color_or = m_board->getBallColor(curr);
        if (!color_or.has_value() || *color_or != origin_color) {
            break;
        }
        tiles.push_back(curr);
    }

    return tiles;
}

int Game::scoreLine(const std::vector<Coordinate> &segment1,
                    const std::vector<Coordinate> &segment2,
                    const int per_ball_score) const
{
    const int line_length = segment1.size() + segment2.size() + 1;
    return line_length >= kMinLine ? line_length * per_ball_score : 0;
}

void Game::removeSegments(const std::vector<Coordinate> &segment1,
                          const std::vector<Coordinate> &segment2)
{
    for (const Coordinate coordinate : segment1) {
        m_board->removeBall(coordinate);
    }
    for (const Coordinate coordinate : segment2) {
        m_board->removeBall(coordinate);
    }
}
