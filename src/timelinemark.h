#pragma once

#include <QGraphicsItem>
#include <QPainter>

class TimelineMark: public QGraphicsItem {
public:
    TimelineMark(int track, qreal xpos, qreal w, QString text);
    bool Overlaps(const TimelineMark *other);
    void IncreaseTrack();
    void SetWidth(qreal w);

    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    qreal getW() const;
    int getTrack() const;

private:
    QColor color;
    QString text;
    qreal w;
    qreal xpos;
    int track;
};
