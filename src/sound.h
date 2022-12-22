#pragma once

#include <QObject>
#include <QMediaPlayer>
#include <QUrl>

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
    Sound(const QUrl &source, QObject *parent = nullptr);
    ~Sound(void);

    bool Play(int masterVolume); // Play sound, return true if it was previously stopped.
    bool Stop(void); // Stop sound, return true if it was previously playing.

    QUrl Source(void) const { return source; }

    bool oneShot {true};

    void setVolume(int volume);
    int getVolume() const;

private slots:
    void printMediaStatus(QMediaPlayer::MediaStatus status);
    void printMediaError(QMediaPlayer::Error error);
};
