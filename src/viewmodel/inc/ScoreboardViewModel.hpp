#pragma once

#include <QObject>
#include <QVariantList>
#include <QVariantMap>

#include <BowlingGame.hpp>

/**
 * @file ScoreboardViewModel.hpp
 * @brief View model declarations for the bowling scoreboard UI.
 */

/**
 * @brief View model that exposes bowling frame and score data to QML.
 *
 * The view model wraps the core BowlingGame engine and translates its frame
 * status into QML-friendly QVariantMap objects.
 */
class ScoreboardViewModel : public QObject
{
    Q_OBJECT

    /**
     * @brief Frame status list exposed to QML.
     */
    Q_PROPERTY(QVariantList frames READ frames NOTIFY framesChanged)

    /**
     * @brief Total game score exposed to QML.
     */
    Q_PROPERTY(int totalScore READ totalScore NOTIFY totalScoreChanged)

    /**
     * @brief Whether the current game has finished.
     */
    Q_PROPERTY(bool isFinished READ isFinished NOTIFY isFinishedChanged)

  public:
    explicit ScoreboardViewModel(QObject *parent = nullptr);

    /**
     * @brief Handle a new bowling roll from the network layer or UI.
     * @param pins Number of pins knocked down.
     */
    Q_INVOKABLE void roll(int pins);

    /**
     * @brief Reset the current bowling game state.
     */
    Q_INVOKABLE void reset();

    /**
     * @brief Retrieve the current frame list for QML binding.
     * @return A list of frame dictionaries.
     */
    QVariantList frames() const;

    int totalScore() const { return m_game.score(); }
    bool isFinished() const { return m_game.isFinished(); }

  signals:
    void framesChanged();
    void totalScoreChanged();
    void isFinishedChanged();

  private:
    BowlingGame m_game; /**< Core scoring engine instance. */

    /**
     * @brief Convert a core frame status object to a QML-friendly map.
     * @param status Frame status from the BowlingGame engine.
     * @param index Zero-based frame index.
     * @return QVariantMap with display values for the frame.
     */
    QVariantMap wrapFrame(const BowlingGame::FrameStatus &status, int index) const;
};
