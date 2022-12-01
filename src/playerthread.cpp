//
// Created by Aleksa Stevic on 1.12.22..
//

#include "playerthread.h"

PlayerThread::PlayerThread(QObject *parent) : QThread(parent) {

}

void PlayerThread::run() {
    unsigned i = 0;
    while (i++ < 100) {
        QThread::msleep(100);
        qDebug("Run tick");
    }
}
