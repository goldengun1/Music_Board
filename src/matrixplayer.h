#pragma once

#include "matrix.h"
#include "playerthread.h"
#include "recorder.h"
#include "soundplayer.h"
#include <QDebug>
#include <QMutex>
#include <QObject>

class MatrixPlayer: public QObject
{
	Q_OBJECT

  public:
	explicit MatrixPlayer(std::shared_ptr<Recorder> recorder, std::shared_ptr<SoundPlayer> player,
	                      QObject *parent = nullptr);
	~MatrixPlayer();

	void PlayMatrix();
	void Stop(void);
	void Pause(void);
	void DeleteMatrix(void);
	bool loopPlaying = false;

  private:
	std::shared_ptr<SoundPlayer> player;
	std::shared_ptr<Recorder> recorder;
	PlayerThread *playerthread;
	QMutex mutex;

	void DeleteThread(void);

  private slots:
	void onPlayFinished();
	void markHit(mark_t mark);
	void onValueChanged(int value);

  signals:
	void matrixEnd();
	void valueChanged(int value);
};
