#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include "soundplayer.h"
#include "matrixplayer.h"
#include "recorder.h"
#include <thread>
#include <headers/utils.h>

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
    void recordStart();
    void recordDelete();
    void recordStop();
    void recordPlay();
    void saveMatrix();
    void importMatrix();
    void recordPause();
    void loopToggle(bool checked);
    void handleSoundButtonPress();
    void handleSoundButtonRelease();
    void handleVolumeChange(int volume);
    void handleOneShotChange(bool state);
    void on_volumeSlider_valueChanged(int value);
    void on_masterVolumeSlider_valueChanged(int value);
    void on_radioTheme2_clicked();
    void on_radioTheme1_clicked();
    void on_radioTheme3_clicked();
    void on_radioPreset1_toggled(bool checked);
    void on_radioPreset2_clicked();
    void on_radioPreset3_clicked();
    void on_radioPreset4_clicked();
    void on_radioPreset5_clicked();
    void on_progressBar_valueChanged(int value);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;


private:
    Ui::MainWindow *ui;
    std::shared_ptr<SoundPlayer> player;
    std::unique_ptr<MatrixPlayer> matrixPlayer;
    std::shared_ptr<Recorder> recorder;
    std::shared_ptr<SoundBank> bank;
    SoundButton *lastClickedBtn;

    void initButtons();
    void initSoundEditing();
    void initToolTips();
};
#endif // MAINWINDOW_H
