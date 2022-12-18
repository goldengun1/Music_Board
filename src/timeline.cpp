#include <QDebug>
#include "timeline.h"
#include "timelinemark.h"

Timeline::Timeline(std::shared_ptr<SoundBank> &bank, QObject *parent)
    : QGraphicsScene(parent)
    , bank{bank} {
}

void Timeline::PaintMatrix(Matrix m) {
    this->clear();
    qreal pos = 0;
    while (!m.timeline.empty()) {
        auto top = m.timeline.top();
        m.timeline.pop();
        if (top.first.second != marktype_t::MARK_PUSH) continue;

        auto sound = bank->Assigned(top.second);
        if (!sound.has_value()) continue;

        auto mark = new TimelineMark(pos, 100, 30, sound.value()->Source().fileName());
        this->addItem(mark);
        pos += TimelineMark::WIDTH;
    }
}

QGraphicsView *Timeline::GetGraphicsView() const {
    if (this->views().empty()) {
        qDebug() << "This scene is not added to any graphics views.";
    }

    return this->views().first();
}

