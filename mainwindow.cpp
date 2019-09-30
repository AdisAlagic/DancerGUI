#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

String MainWindow::buildCommand(){
    String res;
    res = appName + " -title=" + "\"" + songName + "\" " + "-difficulty=" + "\"" + difficuty + "\" ";
    if (cursors != 0){
       res += " -cursors=" + std::to_string(cursors);
    }
    if (pitch != 0.0){
       res += " -pitch=" + std::to_string(pitch);
    }
    if (speed != 0.0){
       res += " -speed=" + std::to_string(speed);
    }
    if (tag != 0){
       res += " -tag=" + std::to_string(tag);
    }
    if (sittings != 0){
        res += " -sittings=" + std::to_string(sittings);
    }
    if (mover != "flower"){
        res += " -mover=" + mover;
    }
    if (fps){
        res += " -fps";
    }
    if (debug){
        res += " -debug";
    }

    return res;
}

void MainWindow::onAnyClick(){
    this->difficuty = ui->cSongDifficulty->currentText().toStdString();
    this->songName = ui->SongSelection->currentText().toStdString();
    this->mover = ui->mover->currentText().toStdString();

    this->pitch = ui->pitch->value();

    this->speed = ui->speed->value();
    this->cursors = ui->cursor->text().toInt();
    this->tag = ui->tag->text().toInt();
    this->sittings = ui->sittings->text().toInt();

    this->fps = ui->fps->isChecked();
    this->debug = ui->debug->isChecked();

    QString comm;
    comm = comm.fromStdString(buildCommand());
    ui->command->setText(comm);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    onAnyClick();
}

void MainWindow::on_SongSelection_currentTextChanged(const QString &arg1)
{
    (void)arg1;
    onAnyClick();
}

void MainWindow::on_cSongDifficulty_currentTextChanged(const QString &arg1)
{
    (void)arg1;
    onAnyClick();
}

void MainWindow::on_cursor_valueChanged(const QString &arg1)
{
    (void)arg1;
    onAnyClick();
}

void MainWindow::on_tag_valueChanged(const QString &arg1)
{
    (void)arg1;
    onAnyClick();
}

void MainWindow::on_pitch_valueChanged(const QString &arg1)
{
    (void)arg1;
    onAnyClick();
}

void MainWindow::on_sittings_valueChanged(const QString &arg1)
{
    (void)arg1;
    onAnyClick();
}

void MainWindow::on_mover_currentTextChanged(const QString &arg1)
{
    (void)arg1;
    onAnyClick();
}

void MainWindow::on_fps_stateChanged(int arg1)
{
    (void)arg1;
    onAnyClick();
}

void MainWindow::on_debug_stateChanged(int arg1)
{
    (void)arg1;
    onAnyClick();
}

void MainWindow::on_speed_valueChanged(const QString &arg1)
{
    (void)arg1;
    onAnyClick();
}
