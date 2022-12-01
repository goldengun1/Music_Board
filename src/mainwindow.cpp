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
    matrixPlayer = std::make_unique<MatrixPlayer>(bank, this);
    recorder = std::make_unique<Recorder>();
    qRegisterMetaType<sid>("sid");
    initButtons();

    // Default bank configuration.
    bank->Assign(0, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Ay.wav"));
    bank->Assign(1, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Bass1.wav"));
    bank->Assign(2, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Bass2.wav"));
    bank->Assign(3, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Bass4.wav"));
    bank->Assign(4, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Gitara1.wav"));
    bank->Assign(5, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Gitara2.wav"));
    bank->Assign(6, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Gitara3.wav"));
    bank->Assign(7, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Gitara4.wav"));
    bank->Assign(8, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Cinela1.wav"));
    bank->Assign(9, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Cinela2.wav"));
    bank->Assign(10, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Tam1.wav"));
    bank->Assign(11, QUrl::fromLocalFile("../05-muzicka-tabla/src/resursi/zvukovi/Tam2.wav"));

    connect(ui->pbRecord, &QPushButton::clicked, this, &MainWindow::recordStart);
    connect(ui->pbPlay, &QPushButton::clicked, this, &MainWindow::recordPlay);
    connect(ui->pbStop, &QPushButton::clicked, this, &MainWindow::recordStop);
    connect(ui->pbDelete, &QPushButton::clicked, this, &MainWindow::recordDelete);
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
    if (recorder->Recording())
    {
        recorder->Mark(button->id);
    }
}

void MainWindow::recordStart()
{
    qDebug() << "Recording: start!";
    recorder->Start();
}

void MainWindow::recordDelete()
{
    qDebug() << "Recording: reset!";
    recorder->Reset();
}

void MainWindow::recordStop()
{
    uint64_t length;
    qDebug() << "Recording: stop!";

    std::tie(length, matrix) = recorder->Stop();
}

void MainWindow::recordPlay()
{
    qDebug() << "Recording: play!";
    matrixPlayer->PlayMatrix(matrix);
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    ui->lcdVolDisplay->display(value);
}


void MainWindow::on_radioTheme2_clicked()
{
    //prebaciti na drugu temu
}

void MainWindow::on_radioTheme1_clicked()
{
    //staviti main temu
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

#if 0
    Matrix m;
    m.Append(0, 1);
    m.Append(1, 3);
    m.Append(5, 10);
    m.Append(6, 0);
    m.Append(10, 3);
    m.Append(11, 1);

    matrixPlayer->PlayMatrix(m);
#endif
}




