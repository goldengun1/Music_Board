//
// Created by Aleksa Stevic on 10.12.22..
//

#include "timelinemark.h"

#include <QRandomGenerator>

TimelineMark::TimelineMark(qreal w)
    : QGraphicsItem()
    , w{w} {
    auto r = QRandomGenerator::global()->bounded(255);
    auto g = QRandomGenerator::global()->bounded(255);
    auto b = QRandomGenerator::global()->bounded(255);

    color = QColor::fromRgb(r, g, b);
}

QRectF TimelineMark::boundingRect() const {
    return{0, 0, w, TimelineMark::HEIGHT};
}

void TimelineMark::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->fillRect(boundingRect(), color);
    painter->drawText(boundingRect().adjusted(10, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, "Hello");
    painter->setPen(Qt::SolidLine);
}
