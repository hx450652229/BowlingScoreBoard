#include "BowlingGame.hpp"

void BowlingGame::roll(int pins) {
    if (pins < 0 || pins > ALL_PINS) {
        throw std::invalid_argument("Pins must be between 0 and 10");
    }
    if (isFinished()) {
        return; // 或者抛出错误
    }
    m_rolls.push_back(pins);
}

int BowlingGame::score() const {
    int totalScore = 0;
    int rollIndex = 0;

    for (int frame = 0; frame < MAX_FRAMES; ++frame) {
        if (rollIndex >= m_rolls.size()) break;

        if (isStrike(rollIndex)) {
            totalScore += ALL_PINS + strikeBonus(rollIndex);
            rollIndex += 1;
        } else if (isSpare(rollIndex)) {
            totalScore += ALL_PINS + spareBonus(rollIndex);
            rollIndex += 2;
        } else {
            totalScore += sumOfBallsInFrame(rollIndex);
            rollIndex += 2;
        }
    }
    return totalScore;
}

std::vector<BowlingGame::FrameStatus> BowlingGame::getFramesStatus() const {
    std::vector<FrameStatus> statuses;
    int rollIndex = 0;
    int currentCumulativeScore = 0;

    for (int frame = 0; frame < MAX_FRAMES; ++frame) {
        FrameStatus status;
        
        if (rollIndex < m_rolls.size()) {
            if (frame < 9) { // 第 1-9 局
                if (isStrike(rollIndex)) {
                    status.rolls.push_back(m_rolls[rollIndex]);
                    if (rollIndex + 2 < m_rolls.size()) {
                        currentCumulativeScore += ALL_PINS + strikeBonus(rollIndex);
                        status.cumulativeScore = currentCumulativeScore;
                        status.isCompleted = true;
                    }
                    rollIndex += 1;
                } else {
                    status.rolls.push_back(m_rolls[rollIndex]);
                    if (rollIndex + 1 < m_rolls.size()) {
                        status.rolls.push_back(m_rolls[rollIndex + 1]);
                        if (isSpare(rollIndex)) {
                            if (rollIndex + 2 < m_rolls.size()) {
                                currentCumulativeScore += ALL_PINS + spareBonus(rollIndex);
                                status.cumulativeScore = currentCumulativeScore;
                                status.isCompleted = true;
                            }
                        } else {
                            currentCumulativeScore += sumOfBallsInFrame(rollIndex);
                            status.cumulativeScore = currentCumulativeScore;
                            status.isCompleted = true;
                        }
                        rollIndex += 2;
                    } else {
                        rollIndex += 1; // 这一局还没投完
                    }
                }
            } else { // 第 10 局特殊规则
                status.rolls.push_back(m_rolls[rollIndex]);
                if (rollIndex + 1 < m_rolls.size()) {
                    status.rolls.push_back(m_rolls[rollIndex + 1]);
                    // 如果前两球总和 >= 10，则有第三球
                    if (m_rolls[rollIndex] + m_rolls[rollIndex+1] >= ALL_PINS) {
                        if (rollIndex + 2 < m_rolls.size()) {
                            status.rolls.push_back(m_rolls[rollIndex + 2]);
                            currentCumulativeScore += m_rolls[rollIndex] + m_rolls[rollIndex+1] + m_rolls[rollIndex+2];
                            status.cumulativeScore = currentCumulativeScore;
                            status.isCompleted = true;
                        }
                    } else {
                        currentCumulativeScore += m_rolls[rollIndex] + m_rolls[rollIndex+1];
                        status.cumulativeScore = currentCumulativeScore;
                        status.isCompleted = true;
                    }
                }
                break; // 第10局处理完直接结束
            }
        }
        statuses.push_back(status);
    }
    return statuses;
}

bool BowlingGame::isFinished() const {
    auto statuses = getFramesStatus();
    if (statuses.size() < MAX_FRAMES) return false;
    return statuses.back().isCompleted;
}

void BowlingGame::reset() {
    m_rolls.clear();
}

// 内部辅助私有实现
bool BowlingGame::isStrike(int rollIndex) const {
    return rollIndex < m_rolls.size() && m_rolls[rollIndex] == ALL_PINS;
}

bool BowlingGame::isSpare(int rollIndex) const {
    if (rollIndex + 1 >= m_rolls.size()) return false;
    return m_rolls[rollIndex] + m_rolls[rollIndex + 1] == ALL_PINS;
}

int BowlingGame::strikeBonus(int rollIndex) const {
    int bonus = 0;
    if (rollIndex + 1 < m_rolls.size()) bonus += m_rolls[rollIndex + 1];
    if (rollIndex + 2 < m_rolls.size()) bonus += m_rolls[rollIndex + 2];
    return bonus;
}

int BowlingGame::spareBonus(int rollIndex) const {
    if (rollIndex + 2 < m_rolls.size()) return m_rolls[rollIndex + 2];
    return 0;
}

int BowlingGame::sumOfBallsInFrame(int rollIndex) const {
    int sum = m_rolls[rollIndex];
    if (rollIndex + 1 < m_rolls.size()) sum += m_rolls[rollIndex + 1];
    return sum;
}