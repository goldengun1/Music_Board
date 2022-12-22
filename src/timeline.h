//
// Created by Aleksa Stevic on 10.12.22..
//

#ifndef INC_05_MUZICKA_TABLA_TIMELINE_H
#define INC_05_MUZICKA_TABLA_TIMELINE_H

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

    QGraphicsView *GetGraphicsView() const;

public:
    void PaintMatrix(Matrix m);
};


#endif //INC_05_MUZICKA_TABLA_TIMELINE_H
