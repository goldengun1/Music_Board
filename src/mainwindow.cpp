#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbQ, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);
    connect(ui->pbW, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);
    connect(ui->pbE, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);
    connect(ui->pbR, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);

    connect(ui->pbA, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);
    connect(ui->pbS, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);
    connect(ui->pbD, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);
    connect(ui->pbF, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);

    connect(ui->pbZ, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);
    connect(ui->pbX, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);
    connect(ui->pbC, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);
    connect(ui->pbV, &SoundButton::rightClicked, this, &MainWindow::onRightClicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onRightClicked(SoundButton *button)
{
    std::cout << "User right clicked " + button->text().toStdString() << std::endl;
}
