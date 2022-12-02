#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QFileDialog>
#include <QDebug>
#include "soundplayer.h"

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
    void handleSoundButtonClick();
    void handleVolumeChange(int volume);

    void on_volumeSlider_valueChanged(int value);

    void on_radioTheme2_clicked();
    void on_radioTheme1_clicked();


private:
    Ui::MainWindow *ui;
    std::unique_ptr<SoundPlayer> player;
    std::shared_ptr<SoundBank> bank;
    SoundButton *lastClickedBtn;

    void initButtons();
    void initSoundEditing();
};
#endif // MAINWINDOW_H
