#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <headers/utlis.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , bank(std::make_shared<SoundBank>(SoundBank()))
{
    ui->setupUi(this);
    player = std::make_unique<SoundPlayer>(SoundPlayer(bank));
    initButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFileDialog(SoundButton *button)
{
    QUrl qUrl = QUrl("/");
    qUrl.setScheme("file");
    auto url = QFileDialog::getOpenFileUrl(this,
        tr("Open audio file"), qUrl, tr("Audio files (*.wav)"));
    if(!url.isEmpty()){
        bank.get()->Assign(button->id, url);
    }
}

void MainWindow::playSound()
{
    auto button = qobject_cast<SoundButton *>(sender());
    if(!player->Play(button->id)){
       //TODO
       qDebug() << "play fail";
    }
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    ui->lcdVolDisplay->display(value);
}


void MainWindow::on_radioTheme2_clicked()
{
    QString stylePath = "/SyNet.qss";

    QString styleSheetData = QString(Utlis::readJsonFromFile(stylePath));
    this->setStyleSheet(styleSheetData);
}

void MainWindow::on_radioTheme1_clicked()
{
    QString stylePath = "/Darkeum.qss";

    QString styleSheetData = QString(Utlis::readJsonFromFile(stylePath));
    this->setStyleSheet(styleSheetData);
}

void MainWindow::initButtons()
{
    ui->pbQ->id = 0;
    ui->pbW->id = 1;
    ui->pbE->id = 2;
    ui->pbR->id = 3;

    ui->pbA->id = 4;
    ui->pbS->id = 5;
    ui->pbW->id = 6;
    ui->pbD->id = 7;

    ui->pbZ->id = 8;
    ui->pbX->id = 9;
    ui->pbC->id = 10;
    ui->pbV->id = 11;

    connect(ui->pbQ, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);
    connect(ui->pbW, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);
    connect(ui->pbE, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);
    connect(ui->pbR, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);

    connect(ui->pbA, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);
    connect(ui->pbS, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);
    connect(ui->pbD, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);
    connect(ui->pbF, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);

    connect(ui->pbZ, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);
    connect(ui->pbX, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);
    connect(ui->pbC, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);
    connect(ui->pbV, &SoundButton::rightClicked, this, &MainWindow::openFileDialog);

    connect(ui->pbQ, &SoundButton::clicked, this, &MainWindow::playSound);
    connect(ui->pbW, &SoundButton::clicked, this, &MainWindow::playSound);
    connect(ui->pbE, &SoundButton::clicked, this, &MainWindow::playSound);
    connect(ui->pbR, &SoundButton::clicked, this, &MainWindow::playSound);

    connect(ui->pbA, &SoundButton::clicked, this, &MainWindow::playSound);
    connect(ui->pbS, &SoundButton::clicked, this, &MainWindow::playSound);
    connect(ui->pbD, &SoundButton::clicked, this, &MainWindow::playSound);
    connect(ui->pbF, &SoundButton::clicked, this, &MainWindow::playSound);

    connect(ui->pbZ, &SoundButton::clicked, this, &MainWindow::playSound);
    connect(ui->pbX, &SoundButton::clicked, this, &MainWindow::playSound);
    connect(ui->pbC, &SoundButton::clicked, this, &MainWindow::playSound);
    connect(ui->pbV, &SoundButton::clicked, this, &MainWindow::playSound);
}




