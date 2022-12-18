#include <utility>
#include "timelinemark.h"
#include "headers/utlis.h"

TimelineMark::TimelineMark(qreal xpos, qreal w, qreal h, QString text)
    : QGraphicsItem()
    , color{Utlis::randomColor()}
    , text{std::move(text)}
    , w{w}
    , h{h} {
    this->setPos(xpos, 0);
}

QRectF TimelineMark::boundingRect() const {
    return{0, 0, w, h};
}

void TimelineMark::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->fillRect(boundingRect(), color);
    painter->drawText(boundingRect().adjusted(10, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
    QPen pen{QBrush(Qt::NoBrush), 5, Qt::SolidLine, Qt::FlatCap};
    pen.setColor(Qt::white);
    painter->setPen(pen);
    painter->drawLine(boundingRect().bottomLeft(), boundingRect().topLeft());
    painter->drawLine(boundingRect().bottomRight(), boundingRect().topRight());
}
