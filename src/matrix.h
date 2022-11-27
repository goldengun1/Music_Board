#pragma once

#include <vector>
#include <QString>
#include "soundbank.h" // For "sid" type.

class Matrix
{
    std::vector<std::pair<uint32_t, sid>> timeline;

public:
    void     Clear(void);
    uint32_t Append(std::pair<uint32_t, sid>);
    uint32_t Append(uint32_t, sid);
    void     Export(const QString &);
};
