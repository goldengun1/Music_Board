#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QUrl>
#include <QDebug>

///
/// Play sound files.
/// Meant to be held by a SoundBank object.
/// Source can be a local file, example - QUrl::fromLocalFile("path...").
///
class Sound: public QObject
{
    Q_OBJECT
    QMediaPlayer player;
    const QUrl source;
    qreal effectVolume {1};

public:
    explicit Sound(const QUrl &source, QObject *parent = nullptr);
    ~Sound(void) override;

    bool oneShot {true};
    bool Play(int masterVolume); // Play sound, return true if it was previously stopped.
    bool Stop(void); // Stop sound, return true if it was previously playing.
    bool IsPlaying() const;
    void setVolume(int volume);

    [[nodiscard]] quint64 Duration() const;
    [[nodiscard]] QUrl Source(void) const { return source; }
    [[nodiscard]] int getVolume() const;

private slots:
    void printMediaStatus(QMediaPlayer::MediaStatus status);
    void printMediaError(QMediaPlayer::Error error);
};
