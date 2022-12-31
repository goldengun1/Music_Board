#include <array>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , bank(std::make_shared<SoundBank>())
{
    ui->setupUi(this);
    player = std::make_shared<SoundPlayer>(bank);
    recorder = std::make_shared<Recorder>();
    matrixPlayer = std::make_unique<MatrixPlayer>(recorder, player, this);
    timeline = std::make_unique<Timeline>(bank, this);
    qRegisterMetaType<sid>("sid");
    qRegisterMetaType<mark_t>("mark_t");
    initButtons();
    initTimeline();
    initToolTips();

    // Default bank configuration.
    on_radioPreset1_toggled(true);

    lastClickedBtn = ui->pbQ;
    initSoundEditing();

    connect(matrixPlayer.get(), &MatrixPlayer::matrixEnd, recorder.get(), &Recorder::handleMatrixEnd);
    connect(matrixPlayer.get(), &MatrixPlayer::valueChanged, this, &MainWindow::on_progressBar_valueChanged);
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
        bank->Assign(button->id, url);
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
        if (recorder->Recording()){
            recorder->Mark(button->id, MARK_PUSH);
        }
        Sound* s = mappedSound->get();
        ui->oneShotCB->setChecked(s->oneShot);
        ui->volumeSlider->setSliderPosition(s->getVolume());
        ui->lcdVolDisplay->display(s->getVolume());
    }


}

void MainWindow::recordStart()
{
    qDebug() << "Recording: start!";
    recorder->Start();
    matrixPlayer->PlayMatrix();
}

void MainWindow::recordDelete()
{
    qDebug() << "Recording: reset!";
    recorder->Reset();
    matrixPlayer->Stop();
    ui->progressBar->setValue(0);
    timeline->clear();
}

void MainWindow::recordStop()
{
    qDebug() << "Recording: stop!";
    if(recorder->Recording()){
        recorder->Stop();
        timeline->PaintMatrix(recorder->getMatrix());
    }
}

void MainWindow::recordPlay()
{
    if(recorder->longestRecordingDuration != 0)
        ui->progressBar->setRange(0,(int)recorder->longestRecordingDuration);
    qDebug() << "Recording: play!";
    matrixPlayer->PlayMatrix();
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

    QString styleSheetData = QString(Utils::readJsonFromFile(stylePath));
    this->setStyleSheet(styleSheetData);
}


void MainWindow::on_radioTheme2_clicked()
{
    QString stylePath = ":/src/teme/SyNet.qss";

    QString styleSheetData = QString(Utils::readJsonFromFile(stylePath));
    this->setStyleSheet(styleSheetData);
}

void MainWindow::on_radioTheme1_clicked()
{
    QString stylePath = ":/src/teme/Darkeum.qss";

    QString styleSheetData = QString(Utils::readJsonFromFile(stylePath));
    this->setStyleSheet(styleSheetData);
}

void MainWindow::initSoundEditing()
{
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::handleVolumeChange);
    connect(ui->oneShotCB, &QCheckBox::clicked, this, &MainWindow::handleOneShotChange);
    connect(ui->masterVolumeSlider, &QSlider::valueChanged, player.get(), &SoundPlayer::handleMasterVolumeChange);
}

void MainWindow::initToolTips()
{
    ui->pbRecord->setToolTip("Započni snimanje");
    ui->pbPlay->setToolTip("Započni reprodukciju");
    ui->pbPause->setToolTip("Pauziraj reprodukciju");
    ui->pbStop->setToolTip("Zaustavi snimanje");
    ui->pbDelete->setToolTip("Obriši snimak");
    ui->pbLoop->setToolTip("Neprekidna reprodukcija");

    ui->pbSaveButton->setToolTip("Sačuvaj snimak");
    ui->pbImport->setToolTip("Učitaj snimak");
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
    Matrix matrix = recorder->getMatrix();
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
    matrix.Export(filePath);
}

void MainWindow::importMatrix() {
    QMessageBox::StandardButton reply = QMessageBox::Yes;
    if (recorder->firstRecordingDuration != 0) {
        reply = QMessageBox::question(this, "Poruka", "Ovo će obrisati trenutno snimljenu matricu. Da li ste sigurni da želite da učitate matricu?");
    }

    if (reply == QMessageBox::Yes) {
        auto filePath = QFileDialog::getOpenFileName(this, tr("Open Matrix"), QDir::homePath(), tr("Matrix files (*.matrix)"));
        auto matrixDurationPair = Matrix::Import(filePath);
        auto matrix = matrixDurationPair.first;
        //TODO:set min and max value for timeline, this is not working properly

        auto duration = matrixDurationPair.second;
        ui->progressBar->setRange(0, (int)duration);
        recorder->firstRecordingDuration = (qint64)duration;
        recorder->longestRecordingDuration = (qint64)duration;
        recorder->setMatrix(matrix);
        timeline->PaintMatrix(matrix);
        //NOTE: trebalo bi ili promeniti tip skladista za matrix, da ne bude std::priority_queue,
        //jer nije moguce pronaci na jednostavan nacin posledji element, ili omoguciti da se info o poslednjem unosu
        //moze naci u samoj klasi kao neki field.
    }
}

void MainWindow::initButtons()
{
    std::array<SoundButton *, 12> sb = { ui->pbQ, ui->pbW, ui->pbE, ui->pbR, ui->pbA, ui->pbS, ui->pbD, ui->pbF, ui->pbZ, ui->pbX, ui->pbC, ui->pbV };

    for (size_t i = 0; i < sb.size(); i++)
    {
        sb.at(i)->id = (uint32_t) i;
        connect(sb.at(i), &SoundButton::rightClicked, this, &MainWindow::openFileDialog);
        connect(sb.at(i), &SoundButton::pressed,      this, &MainWindow::handleSoundButtonPress);
        connect(sb.at(i), &SoundButton::released,     this, &MainWindow::handleSoundButtonRelease);
    }

    //Connect buttons for recording
    connect(ui->pbRecord, &QPushButton::clicked, this, &MainWindow::recordStart);
    connect(ui->pbPlay,   &QPushButton::clicked, this, &MainWindow::recordPlay);
    connect(ui->pbPause,  &QPushButton::clicked, this, &MainWindow::recordPause);
    connect(ui->pbStop,   &QPushButton::clicked, this, &MainWindow::recordStop);
    connect(ui->pbDelete, &QPushButton::clicked, this, &MainWindow::recordDelete);
    connect(ui->pbLoop,   &QPushButton::toggled, this, &MainWindow::loopToggle);

    //Connect recording import/export buttons
    connect(ui->pbSaveButton, &QPushButton::clicked, this, &MainWindow::saveMatrix);
    connect(ui->pbImport,     &QPushButton::clicked, this, &MainWindow::importMatrix);

}

void MainWindow::initTimeline() {
    ui->gvTimeline->setScene(timeline.get());
    ui->gvTimeline->setRenderHint(QPainter::Antialiasing);
    ui->gvTimeline->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

void MainWindow::on_radioPreset1_toggled(bool checked)
{
    if(!checked)
        return;
    bank->Assign(0, QUrl("qrc:/src/resursi/zvukovi/Ay.wav"));
    bank->Assign(1, QUrl("qrc:/src/resursi/zvukovi/Bass1.wav"));
    bank->Assign(2, QUrl("qrc:/src/resursi/zvukovi/Bass2.wav"));
    bank->Assign(3, QUrl("qrc:/src/resursi/zvukovi/Bass4.wav"));
    bank->Assign(4, QUrl("qrc:/src/resursi/zvukovi/Kick.wav"));
    bank->Assign(5, QUrl("qrc:/src/resursi/zvukovi/Dobos1.wav"));
    bank->Assign(6, QUrl("qrc:/src/resursi/zvukovi/Dobos2.wav"));
    bank->Assign(7, QUrl("qrc:/src/resursi/zvukovi/Clap.wav"));
    bank->Assign(8, QUrl("qrc:/src/resursi/zvukovi/Prsti.wav"));
    bank->Assign(9, QUrl("qrc:/src/resursi/zvukovi/Ks1.wav"));
    bank->Assign(10, QUrl("qrc:/src/resursi/zvukovi/Cinela1.wav"));
    bank->Assign(11, QUrl("qrc:/src/resursi/zvukovi/Ding.wav"));
}


void MainWindow::on_radioPreset2_clicked()
{
    bank->Assign(0, QUrl("qrc:/src/resursi/zvukovi/Kick.wav"));
    bank->Assign(1, QUrl("qrc:/src/resursi/zvukovi/Ks1.wav"));
    bank->Assign(2, QUrl("qrc:/src/resursi/zvukovi/Cinela1.wav"));
    bank->Assign(3, QUrl("qrc:/src/resursi/zvukovi/Prsti.wav"));
    bank->Assign(4, QUrl("qrc:/src/resursi/zvukovi/Gitara1.wav"));
    bank->Assign(5, QUrl("qrc:/src/resursi/zvukovi/Gitara2.wav"));
    bank->Assign(6, QUrl("qrc:/src/resursi/zvukovi/Gitara3.wav"));
    bank->Assign(7, QUrl("qrc:/src/resursi/zvukovi/Gitara4.wav"));
    bank->Assign(8, QUrl("qrc:/src/resursi/zvukovi/Orgulje1.wav"));
    bank->Assign(9, QUrl("qrc:/src/resursi/zvukovi/Orgulje2.wav"));
    bank->Assign(10, QUrl("qrc:/src/resursi/zvukovi/Orgulje3.wav"));
    bank->Assign(11, QUrl("qrc:/src/resursi/zvukovi/Orgulje4.wav"));
}


void MainWindow::on_radioPreset3_clicked()
{
//    bank->Assign(0, QUrl("qrc:/src/resursi/zvukovi/piano1.wav"));
//    bank->Assign(1, QUrl("qrc:/src/resursi/zvukovi/piano2.wav"));
//    bank->Assign(2, QUrl("qrc:/src/resursi/zvukovi/piano3.wav"));
//    bank->Assign(3, QUrl("qrc:/src/resursi/zvukovi/piano4.wav"));
//    bank->Assign(4, QUrl("qrc:/src/resursi/zvukovi/piano5.wav"));
//    bank->Assign(5, QUrl("qrc:/src/resursi/zvukovi/piano6.wav"));
//    bank->Assign(6, QUrl("qrc:/src/resursi/zvukovi/piano7.wav"));
//    bank->Assign(7, QUrl("qrc:/src/resursi/zvukovi/piano8.wav"));
//    bank->Assign(8, QUrl("qrc:/src/resursi/zvukovi/piano9.wav"));
//    bank->Assign(9, QUrl("qrc:/src/resursi/zvukovi/piano10.wav"));
//    bank->Assign(10, QUrl("qrc:/src/resursi/zvukovi/piano11.wav"));
//    bank->Assign(11, QUrl("qrc:/src/resursi/zvukovi/piano12.wav"));

      bank->Assign(0, QUrl("qrc:/src/resursi/zvukovi/C.wav"));
      bank->Assign(1, QUrl("qrc:/src/resursi/zvukovi/Cs.wav"));
      bank->Assign(2, QUrl("qrc:/src/resursi/zvukovi/D.wav"));
      bank->Assign(3, QUrl("qrc:/src/resursi/zvukovi/Ds.wav"));
      bank->Assign(4, QUrl("qrc:/src/resursi/zvukovi/E.wav"));
      bank->Assign(5, QUrl("qrc:/src/resursi/zvukovi/F.wav"));
      bank->Assign(6, QUrl("qrc:/src/resursi/zvukovi/Fs.wav"));
      bank->Assign(7, QUrl("qrc:/src/resursi/zvukovi/G.wav"));
      bank->Assign(8, QUrl("qrc:/src/resursi/zvukovi/Gs.wav"));
      bank->Assign(9, QUrl("qrc:/src/resursi/zvukovi/A.wav"));
      bank->Assign(10, QUrl("qrc:/src/resursi/zvukovi/As.wav"));
      bank->Assign(11, QUrl("qrc:/src/resursi/zvukovi/H.wav"));
}


void MainWindow::on_radioPreset4_clicked()
{
    bank->Assign(0, QUrl("qrc:/src/resursi/zvukovi/meme1.wav"));
    bank->Assign(1, QUrl("qrc:/src/resursi/zvukovi/meme2.wav"));
    bank->Assign(2, QUrl("qrc:/src/resursi/zvukovi/meme3.wav"));
    bank->Assign(3, QUrl("qrc:/src/resursi/zvukovi/meme4.wav"));
    bank->Assign(4, QUrl("qrc:/src/resursi/zvukovi/meme5.wav"));
    bank->Assign(5, QUrl("qrc:/src/resursi/zvukovi/meme6.wav"));
    bank->Assign(6, QUrl("qrc:/src/resursi/zvukovi/meme7.wav"));
    bank->Assign(7, QUrl("qrc:/src/resursi/zvukovi/meme8.wav"));
    bank->Assign(8, QUrl("qrc:/src/resursi/zvukovi/meme9.wav"));
    bank->Assign(9, QUrl("qrc:/src/resursi/zvukovi/meme10.wav"));
    bank->Assign(10, QUrl("qrc:/src/resursi/zvukovi/meme11.wav"));
    bank->Assign(11, QUrl("qrc:/src/resursi/zvukovi/meme12.wav"));
}


void MainWindow::on_radioPreset5_clicked()
{
    bank->Assign(0, QUrl("qrc:/src/resursi/zvukovi/SlimShady1.wav"));
    bank->Assign(1, QUrl("qrc:/src/resursi/zvukovi/SlimShady2.wav"));
    bank->Assign(2, QUrl("qrc:/src/resursi/zvukovi/SlimShady3.wav"));
    bank->Assign(3, QUrl("qrc:/src/resursi/zvukovi/SlimShady4.wav"));
    bank->Assign(4, QUrl("qrc:/src/resursi/zvukovi/SlimShady5.wav"));
    bank->Assign(5, QUrl("qrc:/src/resursi/zvukovi/Kick.wav"));
    bank->Assign(6, QUrl("qrc:/src/resursi/zvukovi/SlimShadyDrum1.wav"));
    bank->Assign(7, QUrl("qrc:/src/resursi/zvukovi/Ks1.wav"));
    bank->Assign(8, QUrl("qrc:/src/resursi/zvukovi/SlimShadyBass1.wav"));
    bank->Assign(9, QUrl("qrc:/src/resursi/zvukovi/SlimShadyBass3.wav"));
    bank->Assign(10, QUrl("qrc:/src/resursi/zvukovi/SlimShadyBass4.wav"));
    bank->Assign(11, QUrl("qrc:/src/resursi/zvukovi/SlimShadyBass5.wav"));
}


void MainWindow::on_progressBar_valueChanged(int value)
{
    ui->progressBar->setValue(value);
}
