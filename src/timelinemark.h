//
// Created by Aleksa Stevic on 10.12.22..
//

#ifndef INC_05_MUZICKA_TABLA_TIMELINEMARK_H
#define INC_05_MUZICKA_TABLA_TIMELINEMARK_H

#include <QGraphicsItem>
#include <QPainter>

class TimelineMark: public QGraphicsItem {
public:
    constexpr static const qreal HEIGHT = 30.0;
    constexpr static const qreal WIDTH = 100.0;

    explicit TimelineMark(qreal xpos, qreal w, qreal h, QString text);
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QColor color;
    QString text;
    qreal w;
    qreal h;
};


#endif //INC_05_MUZICKA_TABLA_TIMELINEMARK_H
