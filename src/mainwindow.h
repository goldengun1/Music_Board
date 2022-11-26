#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <iostream>

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
    void onRightClicked(SoundButton *button);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
