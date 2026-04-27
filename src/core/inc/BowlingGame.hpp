#pragma once

#include <numeric>
#include <stdexcept>
#include <vector>

/**
 * @file BowlingGame.hpp
 * @brief Bowling game scoring engine declarations.
 *
 * The core scoring engine implements standard ten-frame bowling rules,
 * including strikes, spares and tenth-frame bonus rolls.
 */

/**
 * @brief Bowling game scoring core logic
 *
 * This class follows standard ten-frame bowling rules and supports strikes,
 * spares, and the tenth-frame bonus rolls.
 */
class BowlingGame
{
  public:
    BowlingGame() = default;

    /**
     * @brief Record the result of a single roll.
     * @param pins Number of pins knocked down.
     * @throws std::invalid_argument If pins is outside the range [0, 10].
     */
    void roll(int pins);

    /**
     * @brief Compute the current total score.
     * @return The total score across all completed frames.
     */
    int score() const;

    /**
     * @brief Get the cumulative score at a specific frame.
     * @param frameIndex One-based frame index in the range [1, 10].
     * @return Cumulative score through the requested frame.
     * @throws std::out_of_range If frameIndex is outside the valid range.
     * @throws std::logic_error If the requested frame score is not yet available.
     */
    int scoreAtFrame(int frameIndex) const;

    /**
     * @brief Describes the status of a single frame.
     */
    struct FrameStatus
    {
        std::vector<int> rolls;   /**< Roll values recorded in this frame. */
        int cumulativeScore = 0;  /**< Score accumulated through this frame. */
        bool isCompleted = false; /**< True when the frame is fully scored. */
    };

    /**
     * @brief Retrieve the status data for all frames.
     * @return A list containing status objects for each frame.
     */
    std::vector<FrameStatus> getFramesStatus() const;

    /**
     * @brief Reset the game state to start a new game.
     */
    void reset();

    /**
     * @brief Check whether the game has completed all ten frames.
     * @return True if the game is finished.
     */
    bool isFinished() const;

  private:
    std::vector<int> m_rolls; /**< Recorded roll values in chronological order. */
    static constexpr int MAX_FRAMES = 10;
    static constexpr int ALL_PINS = 10;

    /**
     * @brief Determine if the roll at rollIndex is a strike.
     * @param rollIndex Index of the roll in m_rolls.
     * @return True if the roll is a strike.
     */
    bool isStrike(int rollIndex) const;

    /**
     * @brief Determine if the frame starting at rollIndex is a spare.
     * @param rollIndex Index of the first roll of the frame.
     * @return True if the frame is a spare.
     */
    bool isSpare(int rollIndex) const;

    /**
     * @brief Calculate the bonus points for a strike.
     * @param rollIndex Index of the strike roll.
     * @return Number of bonus pins from the next two rolls.
     */
    int strikeBonus(int rollIndex) const;

    /**
     * @brief Calculate the bonus points for a spare.
     * @param rollIndex Index of the first roll in the spare frame.
     * @return Number of bonus pins from the next roll.
     */
    int spareBonus(int rollIndex) const;

    /**
     * @brief Sum the pins for a two-roll frame.
     * @param rollIndex Index of the first roll in the frame.
     * @return Total pins knocked down in the frame.
     */
    int sumOfPinsInFrame(int rollIndex) const;
};
