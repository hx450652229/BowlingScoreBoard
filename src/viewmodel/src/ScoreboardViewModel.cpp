#include "ScoreboardViewModel.hpp"

ScoreboardViewModel::ScoreboardViewModel(QObject *parent) 
    : QObject(parent) {}

void ScoreboardViewModel::roll(int pins) {
    try {
        m_game.roll(pins);
        // 数据变了，通知 UI 刷新
        emit framesChanged();
        emit totalScoreChanged();
        emit isFinishedChanged();
    } catch (...) {
        // 生产环境应有更细致的错误处理
    }
}

void ScoreboardViewModel::reset() {
    m_game.reset();
    emit framesChanged();
    emit totalScoreChanged();
    emit isFinishedChanged();
}

QVariantList ScoreboardViewModel::frames() const {
    QVariantList list;
    auto statuses = m_game.getFramesStatus();
    
    for (int i = 0; i < 10; ++i) {
        if (i < statuses.size()) {
            list.append(wrapFrame(statuses[i], i));
        } else {
            // 填充空白局，保证 UI 始终显示 10 个格子
            list.append(wrapFrame({}, i));
        }
    }
    return list;
}

QVariantMap ScoreboardViewModel::wrapFrame(const BowlingGame::FrameStatus& status, int index) const {
    QVariantMap map;
    map["frameNumber"] = index + 1;
    
    // 处理显示逻辑：比如 10 变为 "X"，补中变为 "/"
    auto getDisplay = [&](int rollIdx) -> QString {
        if (rollIdx >= status.rolls.size()) return "";
        int p = status.rolls[rollIdx];
        
        // Strike 逻辑
        if (p == 10) return "X";
        // Spare 逻辑 (第二球且总和为10)
        if (rollIdx == 1 && status.rolls[0] + p == 10) return "/";
        
        return QString::number(p);
    };

    map["t1"] = getDisplay(0);
    map["t2"] = getDisplay(1);
    map["t3"] = getDisplay(2); // 第10局奖励球
    map["score"] = status.isCompleted ? QString::number(status.cumulativeScore) : "";
    
    return map;
}