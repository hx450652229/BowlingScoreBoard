#include "BowlingGame.hpp"
#include <gtest/gtest.h>

class BowlingGameTest : public testing::Test
{
  protected:
    BowlingGame game;

    struct RollCount
    {
        unsigned value;
    };

    void rollMany(RollCount rollCount, int pins)
    {
        for (unsigned i = 0; i < rollCount.value; ++i)
        {
            game.roll(pins);
        }
    }
};

TEST_F(BowlingGameTest, GutterGameScoresZero)
{
    rollMany({ 20 }, 0);
    EXPECT_EQ(game.score(), 0);
    EXPECT_TRUE(game.isFinished());
    for (int frame = 1; frame <= 10; ++frame)
    {
        EXPECT_EQ(game.scoreAtFrame(frame), 0);
    }
}

TEST_F(BowlingGameTest, AllOnesScoresTwenty)
{
    rollMany({ 20 }, 1);
    EXPECT_EQ(game.score(), 20);
    EXPECT_TRUE(game.isFinished());
}

TEST_F(BowlingGameTest, SpareCalculatesBonus)
{
    game.roll(5);
    game.roll(5);
    game.roll(3);
    rollMany({ 17 }, 0);

    EXPECT_EQ(game.score(), 16);
    EXPECT_EQ(game.scoreAtFrame(1), 13);
    EXPECT_EQ(game.scoreAtFrame(2), 16);
    EXPECT_TRUE(game.isFinished());
}

TEST_F(BowlingGameTest, StrikeCalculatesBonus)
{
    game.roll(10);
    game.roll(3);
    game.roll(4);
    rollMany({ 16 }, 0);

    EXPECT_EQ(game.score(), 24);
    EXPECT_EQ(game.scoreAtFrame(1), 17);
    EXPECT_EQ(game.scoreAtFrame(2), 24);
    EXPECT_TRUE(game.isFinished());
}

TEST_F(BowlingGameTest, PerfectGameScores300)
{
    for (int i = 0; i < 12; ++i)
    {
        game.roll(10);
    }

    EXPECT_EQ(game.score(), 300);
    EXPECT_TRUE(game.isFinished());
    EXPECT_EQ(game.scoreAtFrame(10), 300);
}

TEST_F(BowlingGameTest, ResetClearsState)
{
    game.roll(1);
    game.roll(2);
    game.reset();

    EXPECT_EQ(game.score(), 0);
    EXPECT_FALSE(game.isFinished());
    EXPECT_THROW(game.scoreAtFrame(1), std::logic_error);
}

TEST_F(BowlingGameTest, InvalidRollThrows)
{
    EXPECT_THROW(game.roll(-1), std::invalid_argument);
    EXPECT_THROW(game.roll(11), std::invalid_argument);
}
