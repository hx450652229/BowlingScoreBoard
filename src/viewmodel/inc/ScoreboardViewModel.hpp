#pragma once

#include <QObject>
#include <QVariantList>
#include <QVariantMap>

#include <BowlingGame.hpp> // 链接到 Core

class ScoreboardViewModel : public QObject {
    Q_OBJECT
    
    // 暴露给 QML 的属性：每一局的具体数据列表
    Q_PROPERTY(QVariantList frames READ frames NOTIFY framesChanged)
    // 当前总分
    Q_PROPERTY(int totalScore READ totalScore NOTIFY totalScoreChanged)
    // 游戏是否已结束
    Q_PROPERTY(bool isFinished READ isFinished NOTIFY isFinishedChanged)

public:
    explicit ScoreboardViewModel(QObject *parent = nullptr);

    // Q_INVOKABLE 使得 QML 可以直接调用这个 C++ 函数进行测试
    Q_INVOKABLE void roll(int pins);
    Q_INVOKABLE void reset();

    // Getter
    QVariantList frames() const;
    int totalScore() const { return m_game.score(); }
    bool isFinished() const { return m_game.isFinished(); }

signals:
    void framesChanged();
    void totalScoreChanged();
    void isFinishedChanged();

private:
    BowlingGame m_game; // 组合 Core 逻辑
    
    // 辅助函数：将 Core 的 FrameStatus 转为 QML 能懂的字典对象
    QVariantMap wrapFrame(const BowlingGame::FrameStatus& status, int index) const;
};