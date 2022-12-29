#pragma once

#include "matrix.h"
#include <QDebug>
#include <QMutex>
#include <QSemaphore>
#include <QThread>

class PlayerThread: public QThread
{
	Q_OBJECT
  public:
	bool pause;
	QMutex *mutex;

	explicit PlayerThread(QMutex *mutex, QObject *parent = nullptr);
	~PlayerThread(void)
	{
	}

	void Pause(void)
	{
		pause = true;
		pausetime.restart();
		pausetime.start();
	}
	void Resume(void)
	{
		pause = false;
		pausetime_accumulated += pausetime.elapsed();
	}
	void NewMatrix(const Matrix &matrix)
	{
		this->matrix = matrix;
	}

	bool Paused(void) const
	{
		return pause;
	}

  protected:
	void run() override;

  private:
	Matrix matrix;

	uint32_t pausetime_accumulated;
	QElapsedTimer pausetime;

  signals:
	void playFinished();
	void markHit(mark_t info);
	void valueChanged(int value);
};
