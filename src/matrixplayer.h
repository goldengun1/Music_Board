#pragma once

#include <QObject>

#include "soundbank.h"
#include "soundplayer.h"
#include "matrix.h"

class MatrixPlayer: public QObject {
    Q_OBJECT

public:
    explicit MatrixPlayer(std::shared_ptr<SoundBank> &bank, QObject *parent = nullptr);
    void PlayMatrix(const Matrix &);

private:
    std::shared_ptr<SoundBank> bank;
    std::unique_ptr<SoundPlayer> player;

private slots:
    void onPlayFinished();
    void playSound(sid sound);
};
