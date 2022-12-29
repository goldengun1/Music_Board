#pragma once

#include "soundbank.h" // For "sid" type.
#include <QFile>
#include <QString>
#include <QTextStream>
#include <queue>

enum marktype_t
{
	MARK_PUSH,
	MARK_RELEASE,
	MARK_REC_STOP
};
using markinfo_t = std::pair<uint32_t, marktype_t>;
using mark_t = std::pair<markinfo_t, sid>;

struct Matrix
{
	const QString FILE_EXT = ".matrix";
	std::priority_queue<mark_t, std::vector<mark_t>, std::greater<mark_t>> timeline;

	Matrix &operator=(Matrix other)
	{
		timeline = other.timeline;
		return *this;
	}

	void Clear(void);
	marktype_t Append(mark_t);
	marktype_t Append(uint32_t, marktype_t, sid);
	void Export(const QString &) const;
	static std::pair<Matrix, uint32_t> Import(const QString &);
	bool Empty() const;
};
