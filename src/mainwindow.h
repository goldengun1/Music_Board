#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include "soundplayer.h"
#include "matrixplayer.h"
#include "recorder.h"

QT_BEGIN_NAMESPACE

class SoundButton;

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFileDialog(SoundButton *button);
    void playSound();
    void recordStart();
    void recordDelete();
    void recordStop();
    void recordPlay();

    void on_verticalSlider_valueChanged(int value);

    void on_radioTheme2_clicked();
    void on_radioTheme1_clicked();


private:
    Ui::MainWindow *ui;
    std::unique_ptr<SoundPlayer> player;
    std::unique_ptr<MatrixPlayer> matrixPlayer;
    std::unique_ptr<Recorder> recorder;
    std::shared_ptr<SoundBank> bank;
    Matrix matrix;

    void initButtons();
};
#endif // MAINWINDOW_H
