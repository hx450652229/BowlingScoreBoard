#pragma once

#include <vector>
#include <numeric>
#include <stdexcept>

/**
 * @brief 纯 C++20 实现的保龄球计分核心逻辑
 * 遵循标准 10 局制规则。
 */
class BowlingGame {
public:
    BowlingGame() = default;

    // 记录一次投球落瓶数
    void roll(int pins);

    // 获取当前总分
    int score() const;

    // 获取某一局的分数 (1-10)
    int scoreAtFrame(int frameIndex) const;

    // 获取某一局的投球表现（用于 UI 显示，如 "X", "/", "7"）
    struct FrameStatus {
        std::vector<int> rolls;
        int cumulativeScore = 0;
        bool isCompleted = false;
    };
    std::vector<FrameStatus> getFramesStatus() const;

    // 重置游戏
    void reset();

    // 游戏是否结束
    bool isFinished() const;

private:
    std::vector<int> m_rolls;
    static constexpr int MAX_FRAMES = 10;
    static constexpr int ALL_PINS = 10;

    // 辅助计算函数
    bool isStrike(int rollIndex) const;
    bool isSpare(int rollIndex) const;
    int strikeBonus(int rollIndex) const;
    int spareBonus(int rollIndex) const;
    int sumOfBallsInFrame(int rollIndex) const;
};