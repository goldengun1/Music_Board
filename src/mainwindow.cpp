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
    lastClickedBtn = ui->pbQ;
    initSoundEditing();
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

void MainWindow::handleSoundButtonClick()
{
    auto button = qobject_cast<SoundButton *>(sender());
    if(!player->Play(button->id)){
       //TODO
       qDebug() << "play fail";
    }

    lastClickedBtn = button;
    std::optional<std::shared_ptr<Sound>> mappedSound = bank->Assigned(button->id);
    if(mappedSound.has_value()){
        ui->oneShotCB->setCheckState(Qt::Checked);
        ui->volumeSlider->setSliderPosition(mappedSound->get()->getVolume());
    }
}

void MainWindow::handleVolumeChange(int volume)
{
    std::optional<std::shared_ptr<Sound>> mappedSound = bank->Assigned(lastClickedBtn->id);
    if(mappedSound.has_value()){
        mappedSound->get()->setVolume(volume);
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

    connect(ui->pbQ, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);
    connect(ui->pbW, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);
    connect(ui->pbE, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);
    connect(ui->pbR, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);

    connect(ui->pbA, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);
    connect(ui->pbS, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);
    connect(ui->pbD, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);
    connect(ui->pbF, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);

    connect(ui->pbZ, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);
    connect(ui->pbX, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);
    connect(ui->pbC, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);
    connect(ui->pbV, &SoundButton::clicked, this, &MainWindow::handleSoundButtonClick);
}

void MainWindow::initSoundEditing()
{
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::handleVolumeChange);
}




