#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <thread>
#include <headers/utlis.h>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , bank(std::make_shared<SoundBank>())
{
    ui->setupUi(this);
    player = std::make_shared<SoundPlayer>(bank);
    matrixPlayer = std::make_unique<MatrixPlayer>(bank, player, this);
    recorder = std::make_unique<Recorder>();
    qRegisterMetaType<sid>("sid");
    qRegisterMetaType<mark_t>("mark_t");
    initButtons();

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
    connect(ui->pbPause, &QPushButton::clicked, this, &MainWindow::recordPause);
    connect(ui->pbStop, &QPushButton::clicked, this, &MainWindow::recordStop);
    connect(ui->pbDelete, &QPushButton::clicked, this, &MainWindow::recordDelete);
    connect(ui->pbSaveButton, &QPushButton::clicked, this, &MainWindow::saveMatrix);
    connect(ui->pbImport, &QPushButton::clicked, this, &MainWindow::importMatrix);
    connect(ui->pbLoop, &QPushButton::toggled, this, &MainWindow::loopToggle);
    lastClickedBtn = ui->pbQ;
    initSoundEditing();

    connect(matrixPlayer.get(), &MatrixPlayer::matrixEnd, recorder.get(), &Recorder::handleMatrixEnd);
    connect(matrixPlayer.get(), &MatrixPlayer::matrixEnd, this, &MainWindow::handleMatrixEnd);
    connect(matrixPlayer.get(),&MatrixPlayer::valueChanged,this,&MainWindow::on_progressBar_valueChanged);
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

        // TODO: Record a press only if a sound is assigned to the button?
    }

    if (recorder->Recording())
    {
        recorder->Mark(button->id, MARK_PUSH);
    }
}

void MainWindow::recordStart()
{
    qDebug() << "Recording: start!";
    if(recorder->firstRecordingDuration != 0)
        matrix = recorder->Stop();
    matrixPlayer->PlayMatrix(matrix);
    recorder->Start();
}

void MainWindow::recordDelete()
{
    qDebug() << "Recording: reset!";
    recorder->Reset();
    matrixPlayer->Stop();
    matrix.Clear();
}

void MainWindow::recordStop()
{
    qDebug() << "Recording: stop!";
    if(recorder->Recording())
        matrix = recorder->Stop();
}

void MainWindow::recordPlay()
{
    ui->progressBar->setRange(0,(int)recorder->firstRecordingDuration);
    qDebug() << "Recording: play!";
    matrixPlayer->PlayMatrix(matrix);
}


void MainWindow::recordPause()
{
    matrixPlayer->Pause();
}

void MainWindow::loopToggle(bool checked)
{
    qDebug() << "looping" << checked;
    matrixPlayer->loopPlaying = checked;
    recorder->loopRecording = checked;
}

void MainWindow::handleSoundButtonRelease()
{
    auto button = qobject_cast<SoundButton *>(sender());
    std::optional<std::shared_ptr<Sound>> mappedSound = bank->Assigned(button->id);
    if (mappedSound.has_value() && !mappedSound->get()->oneShot){
        player->Stop(button->id);
        if (recorder->Recording())
        {
            recorder->Mark(button->id, MARK_RELEASE);
        }
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

void MainWindow::on_masterVolumeSlider_valueChanged(int value)
{
    ui->lcdVolDisplay->display(value);
}
void MainWindow::on_radioTheme3_clicked()
{
    QString stylePath = ":/src/teme/MatfTheme.qss";

    QString styleSheetData = QString(Utlis::readJsonFromFile(stylePath));
    this->setStyleSheet(styleSheetData);
}


void MainWindow::on_radioTheme2_clicked()
{
    QString stylePath = ":/src/teme/SyNet.qss";

    QString styleSheetData = QString(Utlis::readJsonFromFile(stylePath));
    this->setStyleSheet(styleSheetData);
}

void MainWindow::on_radioTheme1_clicked()
{
    QString stylePath = ":/src/teme/Darkeum.qss";

    QString styleSheetData = QString(Utlis::readJsonFromFile(stylePath));
    this->setStyleSheet(styleSheetData);
}

void MainWindow::handleMatrixEnd()
{
    qDebug() << "main window matrix end" << matrixPlayer->loopPlaying;
    if (matrixPlayer->loopPlaying && !matrix.Empty()){
        matrixPlayer->PlayMatrix(matrix);
    }
}

void MainWindow::initSoundEditing()
{
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::handleVolumeChange);
    connect(ui->oneShotCB, &QCheckBox::clicked, this, &MainWindow::handleOneShotChange);
    connect(ui->masterVolumeSlider, &QSlider::valueChanged, player.get(), &SoundPlayer::handleMasterVolumeChange);
}

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

void MainWindow::saveMatrix() {
    if (matrix.Empty()) {
        QMessageBox::information(this, "Poruka", "Matrica još uvek nije snimljena pa je nije moguće sačuvati.");
        return;
    }
    auto filePath = QFileDialog::getSaveFileName(
            this,
            tr("Save Matrix"),
            QDir::homePath(),
            tr("Matrix files (*.matrix)")
        );
    this->matrix.Export(filePath);
}

void MainWindow::importMatrix() {
    QMessageBox::StandardButton reply = QMessageBox::Yes;
    if (!matrix.Empty()) {
        reply = QMessageBox::question(this, "Poruka", "Ovo će obrisati trenutno snimljenu matricu. Da li ste sigurni da želite da učitate matricu?");
    }

    if (reply == QMessageBox::Yes) {
        auto filePath = QFileDialog::getOpenFileName(this, tr("Open Matrix"), QDir::homePath(), tr("Matrix files (*.matrix)"));
        matrix = Matrix::Import(filePath);
        //TODO:set min and max value for timeline, this is not working properly
        int matrixSize = (int)matrix.timeline.size();
        qDebug()<<matrixSize;
        ui->progressBar->setRange(0,matrixSize * 500);

        //NOTE: trebalo bi ili promeniti tip skladista za matrix, da ne bude std::priority_queue,
        //jer nije moguce pronaci na jednostavan nacin posledji element, ili omoguciti da se info o poslednjem unosu
        //moze naci u samoj klasi kao neki field.
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


void MainWindow::on_progressBar_valueChanged(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::on_progresBarr_setup(int min, int max)
{
    ui->progressBar->setRange(min,max);
}

