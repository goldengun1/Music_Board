#include <utility>
#include "timelinemark.h"
#include "headers/utils.h"
#include "matrix.h"

TimelineMark::TimelineMark(int track, qreal xpos, qreal w, QString text)
    : QGraphicsItem()
    , color{Utils::randomColor()}
    , text{std::move(text)}
    , w{w}
    , track{track}
    , xpos{xpos} {
    this->setPos(xpos, track * Utils::TRACK_HEIGHT);
}

QRectF TimelineMark::boundingRect() const {
    return{0, 0, w, Utils::TRACK_HEIGHT};
}

void TimelineMark::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->fillRect(boundingRect(), color);
    painter->drawText(boundingRect().adjusted(10, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
    QPen pen{QBrush(Qt::NoBrush), 1, Qt::SolidLine, Qt::FlatCap};
    pen.setColor(Qt::white);
    painter->setPen(pen);
//    painter->drawLine(boundingRect().bottomLeft(), boundingRect().topLeft());
//    painter->drawLine(boundingRect().bottomRight(), boundingRect().topRight());
    painter->drawRect(boundingRect());
}

bool TimelineMark::Overlaps(const TimelineMark *other) {
    if (track != other->track) return false;

    return (this->x() < other->x() && other->x() < this->x() + w) || (this->x() < other->x() + other->w && other->x() + other->w < this->x() + w)
    || (other->x() < this->x() && this->x() < other->x() + other->w) || (other->x() < this->x() + w && this->x() + w < other->x() + other->w);
}

void TimelineMark::IncreaseTrack() {
    track++;
    this->setPos(xpos, track * Utils::TRACK_HEIGHT);
}

void TimelineMark::SetWidth(qreal width) {
    this->w = width;
}
