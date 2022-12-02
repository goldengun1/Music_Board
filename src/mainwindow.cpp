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

void MainWindow::handleSoundButtonPress()
{
    auto button = qobject_cast<SoundButton *>(sender());
    if(!player->Play(button->id)){
       //TODO
       qDebug() << "play fail";
    }

    lastClickedBtn = button;
    std::optional<std::shared_ptr<Sound>> mappedSound = bank->Assigned(button->id);
    if(mappedSound.has_value()){
        Sound* s = mappedSound->get();
        ui->oneShotCB->setChecked(s->oneShot);
        ui->volumeSlider->setSliderPosition(s->getVolume());
        ui->lcdVolDisplay->display(s->getVolume());
    }
}

void MainWindow::handleSoundButtonRelease()
{
    auto button = qobject_cast<SoundButton *>(sender());
    std::optional<std::shared_ptr<Sound>> mappedSound = bank->Assigned(button->id);
    if (mappedSound.has_value() && !mappedSound->get()->oneShot){
        player->Stop(button->id);
    }
}

void MainWindow::handleVolumeChange(int volume)
{
    std::optional<std::shared_ptr<Sound>> mappedSound = bank->Assigned(lastClickedBtn->id);
    if(mappedSound.has_value()){
        mappedSound->get()->setVolume(volume);
    }
}

void MainWindow::handleOneShotChange(bool state)
{
    std::optional<std::shared_ptr<Sound>> mappedSound = bank->Assigned(lastClickedBtn->id);
    if(mappedSound.has_value()){
        mappedSound->get()->oneShot = state;
    }
}

void MainWindow::on_volumeSlider_valueChanged(int value)
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()){
        switch (event->key()) {
        case Qt::Key_Q:
            emit ui->pbQ->pressed();
            break;
        case Qt::Key_W:
            emit ui->pbW->pressed();
            break;
        case Qt::Key_E:
            emit ui->pbE->pressed();
            break;
        case Qt::Key_R:
            emit ui->pbR->pressed();
            break;
        case Qt::Key_A:
            emit ui->pbA->pressed();
            break;
        case Qt::Key_S:
            emit ui->pbS->pressed();
            break;
        case Qt::Key_D:
            emit ui->pbD->pressed();
            break;
        case Qt::Key_F:
            emit ui->pbF->pressed();
            break;
        case Qt::Key_Z:
            emit ui->pbZ->pressed();
            break;
        case Qt::Key_X:
            emit ui->pbX->pressed();
            break;
        case Qt::Key_C:
            emit ui->pbC->pressed();
            break;
        case Qt::Key_V:
            emit ui->pbV->pressed();
            break;
        default:
            QWidget::keyPressEvent(event);
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()){
        switch (event->key()) {
        case Qt::Key_Q:
            emit ui->pbQ->released();
            break;
        case Qt::Key_W:
            emit ui->pbW->released();
            break;
        case Qt::Key_E:
            emit ui->pbE->released();
            break;
        case Qt::Key_R:
            emit ui->pbR->released();
            break;
        case Qt::Key_A:
            emit ui->pbA->released();
            break;
        case Qt::Key_S:
            emit ui->pbS->released();
            break;
        case Qt::Key_D:
            emit ui->pbD->released();
            break;
        case Qt::Key_F:
            emit ui->pbF->released();
            break;
        case Qt::Key_Z:
            emit ui->pbZ->released();
            break;
        case Qt::Key_X:
            emit ui->pbX->released();
            break;
        case Qt::Key_C:
            emit ui->pbC->released();
            break;
        case Qt::Key_V:
            emit ui->pbV->released();
            break;
        default:
            QWidget::keyPressEvent(event);
        }
    }
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

    connect(ui->pbQ, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);
    connect(ui->pbW, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);
    connect(ui->pbE, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);
    connect(ui->pbR, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);
    connect(ui->pbA, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);
    connect(ui->pbS, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);
    connect(ui->pbD, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);
    connect(ui->pbF, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);
    connect(ui->pbZ, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);
    connect(ui->pbX, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);
    connect(ui->pbC, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);
    connect(ui->pbV, &SoundButton::pressed, this, &MainWindow::handleSoundButtonPress);

    connect(ui->pbQ, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
    connect(ui->pbW, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
    connect(ui->pbE, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
    connect(ui->pbR, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
    connect(ui->pbA, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
    connect(ui->pbS, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
    connect(ui->pbD, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
    connect(ui->pbF, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
    connect(ui->pbZ, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
    connect(ui->pbX, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
    connect(ui->pbC, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
    connect(ui->pbV, &SoundButton::released, this, &MainWindow::handleSoundButtonRelease);
}

void MainWindow::initSoundEditing()
{
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::handleVolumeChange);
    connect(ui->oneShotCB, &QCheckBox::clicked, this, &MainWindow::handleOneShotChange);
}




