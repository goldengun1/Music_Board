//
// Created by Aleksa Stevic on 10.12.22..
//

#ifndef INC_05_MUZICKA_TABLA_TIMELINE_H
#define INC_05_MUZICKA_TABLA_TIMELINE_H

#include <QObject>
#include <QGraphicsView>
#include "soundbank.h"


class Timeline: public QGraphicsScene {
public:
    explicit Timeline(std::shared_ptr<SoundBank> &bank, QObject *parent = nullptr);

private:
    std::shared_ptr<SoundBank> bank;
};


#endif //INC_05_MUZICKA_TABLA_TIMELINE_H
