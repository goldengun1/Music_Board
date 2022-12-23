#pragma once

#include <QObject>
#include <QGraphicsView>
#include "soundbank.h"
#include "matrix.h"
#include "timelinemark.h"


class Timeline: public QGraphicsScene {
public:
    explicit Timeline(std::shared_ptr<SoundBank> &bank, QObject *parent = nullptr);

private:
    std::shared_ptr<SoundBank> bank;
public:
    void PaintMatrix(Matrix m);
};
