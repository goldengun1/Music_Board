//
// Created by Aleksa Stevic on 10.12.22..
//

#ifndef INC_05_MUZICKA_TABLA_TIMELINEMARK_H
#define INC_05_MUZICKA_TABLA_TIMELINEMARK_H

#include <QGraphicsItem>
#include <QPainter>

class TimelineMark: public QGraphicsItem {
    const qreal HEIGHT = 30.0;
public:
    explicit TimelineMark(qreal w);
    [[nodiscard]] QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qreal w;
    QColor color;
};


#endif //INC_05_MUZICKA_TABLA_TIMELINEMARK_H
