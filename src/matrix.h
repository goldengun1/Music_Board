#pragma once

#include <vector>
#include <QString>
#include "soundbank.h" // For "sid" type.

struct Matrix
{
    const QString FILE_EXT = ".matrix";
    std::vector<std::pair<uint32_t, sid>> timeline;

    Matrix &operator=(Matrix other) { timeline = other.timeline; return *this; }

    void            Clear(void);
    uint32_t        Append(std::pair<uint32_t, sid>);
    uint32_t        Append(uint32_t, sid);
    void            Export(const QString &);
    static Matrix   Import(const QString &);
};
