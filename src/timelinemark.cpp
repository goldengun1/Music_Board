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
    QPen pen{QBrush(Qt::NoBrush), 5, Qt::SolidLine, Qt::FlatCap};
    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->drawLine(boundingRect().bottomLeft(), boundingRect().topLeft());
    painter->drawLine(boundingRect().bottomRight(), boundingRect().topRight());
}
