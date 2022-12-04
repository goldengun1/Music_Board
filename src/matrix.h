#pragma once

#include <queue>
#include <QString>
#include "soundbank.h" // For "sid" type.

using mark_t = std::pair<uint32_t, sid>;

struct Matrix
{
    const QString FILE_EXT = ".matrix";
    std::priority_queue<mark_t, std::vector<mark_t>, std::greater<mark_t>> timeline;

    Matrix &operator=(Matrix other) { timeline = other.timeline; return *this; }

    void            Clear(void);
    uint32_t        Append(std::pair<uint32_t, sid>);
    uint32_t        Append(uint32_t, sid);
    void            Export(const QString &);
    static Matrix   Import(const QString &);
};
