#include <QDebug>
#include <vector>
#include "timeline.h"
#include "timelinemark.h"
#include "headers/utils.h"

Timeline::Timeline(std::shared_ptr<SoundBank> &bank, QObject *parent)
    : QGraphicsScene(parent)
    , bank{bank} {
}

void Timeline::PaintMatrix(Matrix m) {
    this->clear();

    std::vector<TimelineMark *> marks;
    TimelineMark *last = nullptr;
    mark_t lastMark;
    while (!m.timeline.empty()) {
        auto top = m.timeline.top();
        m.timeline.pop();
        if (top.first.second == marktype_t::MARK_REC_STOP) continue;

        if (top.first.second == marktype_t::MARK_RELEASE) {
            auto duration = top.first.first - lastMark.first.first;
            last->SetWidth(Utils::MilisecondsToPixel(duration));
            continue;
        }

        auto sound = bank->Assigned(top.second);
        if (!sound.has_value()) continue;

        last = new TimelineMark(0, Utils::MilisecondsToPixel(top.first.first), Utils::MilisecondsToPixel(sound.value()->Duration()), sound.value()->Source().fileName().remove(QRegExp("\\.[^.]+")));
        lastMark = top;
        while(std::any_of(marks.begin(), marks.end(), [&last](const TimelineMark *m) { return last->Overlaps(m); }))
            last->IncreaseTrack();

        marks.push_back(last);
    }

    for (auto mark : marks) {
        this->addItem(mark);
    }
    this->setSceneRect(itemsBoundingRect());
}

QGraphicsView *Timeline::GetGraphicsView() const {
    if (this->views().empty()) {
        qDebug() << "This scene is not added to any graphics views.";
    }

    return this->views().first();
}

