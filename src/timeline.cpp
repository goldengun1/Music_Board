//
// Created by Aleksa Stevic on 10.12.22..
//

#include "timeline.h"
#include "timelinemark.h"

Timeline::Timeline(std::shared_ptr<SoundBank> &bank, QObject *parent)
    : QGraphicsScene(parent)
    , bank{bank} {
    auto tm1 = new TimelineMark(100);
    auto tm2 = new TimelineMark(300);
    tm2->setPos(100, 0);
    this->addItem(tm1);
    this->addItem(tm2);
}
