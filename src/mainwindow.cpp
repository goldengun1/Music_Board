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
    timeline = std::make_unique<Timeline>(bank, this);
    qRegisterMetaType<sid>("sid");
    initButtons();
    initTimeline();

    // Default bank configuration.
    bank->Assign(0, QUrl::fromLocalFile(":/src/resursi/zvukovi/Ay.wav"));
    bank->Assign(1, QUrl::fromLocalFile(":/src/resursi/zvukovi/Bass1.wav"));
    bank->Assign(2, QUrl::fromLocalFile(":/src/resursi/zvukovi/Bass2.wav"));
    bank->Assign(3, QUrl::fromLocalFile(":/src/resursi/zvukovi/Bass4.wav"));
    bank->Assign(4, QUrl::fromLocalFile(":/src/resursi/zvukovi/Kick.wav"));
    bank->Assign(5, QUrl::fromLocalFile(":/src/resursi/zvukovi/Dobos1.wav"));
    bank->Assign(6, QUrl::fromLocalFile(":/src/resursi/zvukovi/Dobos2.wav"));
    bank->Assign(7, QUrl::fromLocalFile(":/src/resursi/zvukovi/Clap.wav"));
    bank->Assign(8, QUrl::fromLocalFile(":/src/resursi/zvukovi/Prsti.wav"));
    bank->Assign(9, QUrl::fromLocalFile(":/src/resursi/zvukovi/Ks1.wav"));
    bank->Assign(10, QUrl::fromLocalFile(":/src/resursi/zvukovi/Cinela1.wav"));
    bank->Assign(11, QUrl::fromLocalFile(":/src/resursi/zvukovi/Ding.wav"));

    connect(ui->pbRecord, &QPushButton::clicked, this, &MainWindow::recordStart);
    connect(ui->pbPlay, &QPushButton::clicked, this, &MainWindow::recordPlay);
    connect(ui->pbStop, &QPushButton::clicked, this, &MainWindow::recordStop);
    connect(ui->pbDelete, &QPushButton::clicked, this, &MainWindow::recordDelete);
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

void MainWindow::on_radioTheme3_clicked()
{
    QString stylePath = "/MatfTheme.qss";

    QString styleSheetData = QString(Utlis::readJsonFromFile(stylePath));
    this->setStyleSheet(styleSheetData);
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

void MainWindow::initSoundEditing()
{
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::handleVolumeChange);
    connect(ui->oneShotCB, &QCheckBox::clicked, this, &MainWindow::handleOneShotChange);
}

//dodati vizualizaciju pritiska tastera preko tastature
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()){
        switch (event->key()) {
        case Qt::Key_Q:
            emit ui->pbQ->pressed();
            ui->pbQ->setDown(true);
            break;
        case Qt::Key_W:
            emit ui->pbW->pressed();
            ui->pbW->setDown(true);
            break;
        case Qt::Key_E:
            emit ui->pbE->pressed();
            ui->pbE->setDown(true);
            break;
        case Qt::Key_R:
            emit ui->pbR->pressed();
            ui->pbR->setDown(true);
            break;
        case Qt::Key_A:
            emit ui->pbA->pressed();
            ui->pbA->setDown(true);
            break;
        case Qt::Key_S:
            emit ui->pbS->pressed();
            ui->pbS->setDown(true);
            break;
        case Qt::Key_D:
            emit ui->pbD->pressed();
            ui->pbD->setDown(true);
            break;
        case Qt::Key_F:
            emit ui->pbF->pressed();
            ui->pbF->setDown(true);
            break;
        case Qt::Key_Z:
            emit ui->pbZ->pressed();
            ui->pbZ->setDown(true);
            break;
        case Qt::Key_X:
            emit ui->pbX->pressed();
            ui->pbX->setDown(true);
            break;
        case Qt::Key_C:
            emit ui->pbC->pressed();
            ui->pbC->setDown(true);
            break;
        case Qt::Key_V:
            emit ui->pbV->pressed();
            ui->pbV->setDown(true);
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
            ui->pbQ->setDown(false);
            break;
        case Qt::Key_W:
            emit ui->pbW->released();
            ui->pbW->setDown(false);
            break;
        case Qt::Key_E:
            emit ui->pbE->released();
            ui->pbE->setDown(false);
            break;
        case Qt::Key_R:
            emit ui->pbR->released();
            ui->pbR->setDown(false);
            break;
        case Qt::Key_A:
            emit ui->pbA->released();
            ui->pbA->setDown(false);
            break;
        case Qt::Key_S:
            emit ui->pbS->released();
            ui->pbS->setDown(false);
            break;
        case Qt::Key_D:
            emit ui->pbD->released();
            ui->pbD->setDown(false);
            break;
        case Qt::Key_F:
            emit ui->pbF->released();
            ui->pbF->setDown(false);
            break;
        case Qt::Key_Z:
            emit ui->pbZ->released();
            ui->pbZ->setDown(false);
            break;
        case Qt::Key_X:
            emit ui->pbX->released();
            ui->pbX->setDown(false);
            break;
        case Qt::Key_C:
            emit ui->pbC->released();
            ui->pbC->setDown(false);
            break;
        case Qt::Key_V:
            emit ui->pbV->released();
            ui->pbV->setDown(false);
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
    ui->pbD->id = 6;
    ui->pbF->id = 7;

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

void MainWindow::initTimeline() {
    timeline->setSceneRect(ui->gvTimeline->rect());
    ui->gvTimeline->setScene(timeline.get());
    ui->gvTimeline->setRenderHint(QPainter::Antialiasing);
    ui->gvTimeline->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

void MainWindow::on_radioPreset1_toggled(bool checked)
{
    if(!checked)
        return;
    bank->Assign(0, QUrl::fromLocalFile(":/src/resursi/zvukovi/Ay.wav"));
    bank->Assign(1, QUrl::fromLocalFile(":/src/resursi/zvukovi/Bass1.wav"));
    bank->Assign(2, QUrl::fromLocalFile(":/src/resursi/zvukovi/Bass2.wav"));
    bank->Assign(3, QUrl::fromLocalFile(":/src/resursi/zvukovi/Bass4.wav"));
    bank->Assign(4, QUrl::fromLocalFile(":/src/resursi/zvukovi/Kick.wav"));
    bank->Assign(5, QUrl::fromLocalFile(":/src/resursi/zvukovi/Dobos1.wav"));
    bank->Assign(6, QUrl::fromLocalFile(":/src/resursi/zvukovi/Dobos2.wav"));
    bank->Assign(7, QUrl::fromLocalFile(":/src/resursi/zvukovi/Clap.wav"));
    bank->Assign(8, QUrl::fromLocalFile(":/src/resursi/zvukovi/Prsti.wav"));
    bank->Assign(9, QUrl::fromLocalFile(":/src/resursi/zvukovi/Ks1.wav"));
    bank->Assign(10, QUrl::fromLocalFile(":/src/resursi/zvukovi/Cinela1.wav"));
    bank->Assign(11, QUrl::fromLocalFile(":/src/resursi/zvukovi/Ding.wav"));
}


void MainWindow::on_radioPreset2_clicked()
{

    bank->Assign(0, QUrl::fromLocalFile(":/src/resursi/zvukovi/Kick.wav"));
    bank->Assign(1, QUrl::fromLocalFile(":/src/resursi/zvukovi/Ks1.wav"));
    bank->Assign(2, QUrl::fromLocalFile(":/src/resursi/zvukovi/Cinela1.wav"));
    bank->Assign(3, QUrl::fromLocalFile(":/src/resursi/zvukovi/Prsti.wav"));
    bank->Assign(4, QUrl::fromLocalFile(":/src/resursi/zvukovi/Gitara1.wav"));
    bank->Assign(5, QUrl::fromLocalFile(":/src/resursi/zvukovi/Gitara2.wav"));
    bank->Assign(6, QUrl::fromLocalFile(":/src/resursi/zvukovi/Gitara3.wav"));
    bank->Assign(7, QUrl::fromLocalFile(":/src/resursi/zvukovi/Gitara4.wav"));
    bank->Assign(8, QUrl::fromLocalFile(":/src/resursi/zvukovi/Orgulje1.wav"));
    bank->Assign(9, QUrl::fromLocalFile(":/src/resursi/zvukovi/Orgulje2.wav"));
    bank->Assign(10, QUrl::fromLocalFile(":/src/resursi/zvukovi/Orgulje3.wav"));
    bank->Assign(11, QUrl::fromLocalFile(":/src/resursi/zvukovi/Orgulje4.wav"));
}


void MainWindow::on_radioPreset3_clicked()
{
    bank->Assign(0, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano1.wav"));
    bank->Assign(1, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano2.wav"));
    bank->Assign(2, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano3.wav"));
    bank->Assign(3, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano4.wav"));
    bank->Assign(4, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano5.wav"));
    bank->Assign(5, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano6.wav"));
    bank->Assign(6, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano7.wav"));
    bank->Assign(7, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano8.wav"));
    bank->Assign(8, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano9.wav"));
    bank->Assign(9, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano10.wav"));
    bank->Assign(10, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano11.wav"));
    bank->Assign(11, QUrl::fromLocalFile(":/src/resursi/zvukovi/piano12.wav"));
}


void MainWindow::on_radioPreset4_clicked()
{
    bank->Assign(0, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme1.wav"));
    bank->Assign(1, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme2.wav"));
    bank->Assign(2, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme3.wav"));
    bank->Assign(3, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme4.wav"));
    bank->Assign(4, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme5.wav"));
    bank->Assign(5, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme6.wav"));
    bank->Assign(6, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme7.wav"));
    bank->Assign(7, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme8.wav"));
    bank->Assign(8, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme9.wav"));
    bank->Assign(9, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme10.wav"));
    bank->Assign(10, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme11.wav"));
    bank->Assign(11, QUrl::fromLocalFile(":/src/resursi/zvukovi/meme12.wav"));
}


void MainWindow::on_radioPreset5_clicked()
{
    bank->Assign(0, QUrl::fromLocalFile(":/src/resursi/zvukovi/SlimShady1.wav"));
    bank->Assign(1, QUrl::fromLocalFile(":/src/resursi/zvukovi/SlimShady2.wav"));
    bank->Assign(2, QUrl::fromLocalFile(":/src/resursi/zvukovi/SlimShady3.wav"));
    bank->Assign(3, QUrl::fromLocalFile(":/src/resursi/zvukovi/SlimShady4.wav"));
    bank->Assign(4, QUrl::fromLocalFile(":/src/resursi/zvukovi/SlimShady5.wav"));
    bank->Assign(5, QUrl::fromLocalFile(":/src/resursi/zvukovi/Kick.wav"));
    bank->Assign(6, QUrl::fromLocalFile(":/src/resursi/zvukovi/SlimShadyDrum1.wav"));
    bank->Assign(7, QUrl::fromLocalFile(":/src/resursi/zvukovi/Ks1.wav"));
    bank->Assign(8, QUrl::fromLocalFile(":/src/resursi/zvukovi/SlimShadyBass1.wav"));
    bank->Assign(9, QUrl::fromLocalFile(":/src/resursi/zvukovi/SlimShadyBass3.wav"));
    bank->Assign(10, QUrl::fromLocalFile(":/src/resursi/zvukovi/SlimShadyBass4.wav"));
    bank->Assign(11, QUrl::fromLocalFile(":/src/resursi/zvukovi/SlimShadyBass5.wav"));
}

