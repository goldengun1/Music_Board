#pragma once

#include <QGraphicsItem>
#include <QPainter>
#include "sound.h"

class TimelineMark: public QGraphicsItem {
public:
    TimelineMark(int track, qreal xpos, qreal w, QString text);
    bool Overlaps(const TimelineMark *other);
    void IncreaseTrack();
    void SetWidth(qreal w);

    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QColor color;
    QString text;
    qreal w;
    qreal xpos;
    int track;
};
