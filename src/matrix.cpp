#include "matrix.h"


void
Matrix::Clear(void)
{
    timeline.clear();
}

uint32_t
Matrix::Append(std::pair<uint32_t, sid> mark)
{
    return Append(mark.first, mark.second);
}

uint32_t
Matrix::Append(uint32_t marktime, sid marksound)
{
    return timeline.emplace_back(marktime, marksound).first;
}

void
Matrix::Export(const QString &)
{

}
