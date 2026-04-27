#include "ScoreboardViewModel.hpp"
#include <QDebug>

ScoreboardViewModel::ScoreboardViewModel(QObject *parent) : QObject(parent) {}

void ScoreboardViewModel::roll(int pins)
{
    try
    {
        m_game.roll(pins);
        // Notify the UI that game data has changed.
        emit framesChanged();
        emit totalScoreChanged();
        emit isFinishedChanged();
    }
    catch (const std::invalid_argument &ex)
    {
        qWarning() << "ScoreboardViewModel::roll failed:" << ex.what();
    }
    catch (const std::exception &ex)
    {
        qWarning() << "ScoreboardViewModel::roll unexpected error:" << ex.what();
        throw;
    }
}

void ScoreboardViewModel::reset()
{
    m_game.reset();
    emit framesChanged();
    emit totalScoreChanged();
    emit isFinishedChanged();
}

QVariantList ScoreboardViewModel::frames() const
{
    QVariantList list;
    auto statuses = m_game.getFramesStatus();

    for (int i = 0; i < 10; ++i)
    {
        if (i < statuses.size())
        {
            list.append(wrapFrame(statuses[i], i));
        }
        else
        {
            // Fill missing frames so the UI always displays ten cells.
            list.append(wrapFrame({}, i));
        }
    }
    return list;
}

QVariantMap ScoreboardViewModel::wrapFrame(const BowlingGame::FrameStatus &status, int index) const
{
    QVariantMap map;
    map["frameNumber"] = index + 1;

    // Convert raw pin values into display strings.
    auto getDisplay = [&](int rollIdx) -> QString
    {
        if (rollIdx >= status.rolls.size())
            return "";
        int p = status.rolls[rollIdx];

        if (p == 10)
            return "X";
        if (rollIdx == 1 && status.rolls[0] + p == 10)
            return "/";

        return QString::number(p);
    };

    map["t1"] = getDisplay(0);
    map["t2"] = getDisplay(1);
    map["t3"] = getDisplay(2); // Bonus roll shown only in the tenth frame.
    map["score"] = status.isCompleted ? QString::number(status.cumulativeScore) : "";

    return map;
}
