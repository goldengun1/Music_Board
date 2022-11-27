#pragma once

#include <vector>
#include <QString>
#include "soundbank.h" // For "sid" type.

struct Matrix
{
    std::vector<std::pair<uint32_t, sid>> timeline;

    void     Clear(void);
    uint32_t Append(std::pair<uint32_t, sid>);
    uint32_t Append(uint32_t, sid);
    void     Export(const QString &);
};
