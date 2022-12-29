#pragma once

#include "matrix.h"
#include "soundbank.h"
#include "timelinemark.h"
#include <QGraphicsView>
#include <QObject>

class Timeline: public QGraphicsScene
{
  public:
	explicit Timeline(std::shared_ptr<SoundBank> &bank, QObject *parent = nullptr);

  private:
	std::shared_ptr<SoundBank> bank;

  public:
	void PaintMatrix(Matrix m);
};
