#include "mainwindow.h"
#include "sqlitemanager.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->start->setEnabled(false);
    if (!scanFolder()){
    tryAgain:
    QMessageBox box("Dancer not found", "Dancer not found, would you like to select exe file?",
                    QMessageBox::Warning, QMessageBox::Yes, QMessageBox::Retry, QMessageBox::No);
    int reply = box.exec();
    switch(reply){
    case QMessageBox::Yes:
        appName = openFile().toStdString();
        if (appName.empty()){
            goto tryAgain;
        }
        setExit(false);
        break;
    case QMessageBox::No:
        setExit(true);
        QApplication::closeAllWindows();
        break;
    case QMessageBox::Retry:
        if(!scanFolder()){
            goto tryAgain;
        }
    }
    pr.setProgram("cmd.exe");
    pr.setWorkingDirectory(getDir().path());
    on_update_clicked();
    }
}

void MainWindow::setSongs(){
    std::vector<QString> songs = sql.getSongs(getDir().path());
    for (auto it : songs){
        ui->SongSelection->addItem(it);
    }

}

QDir MainWindow::getDir(){
    return path;
}

QString MainWindow::openFile(){
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Executable Files (*.exe)");
    path = dialog.directory();
    if (dialog.exec()){
        QStringList fileName = dialog.selectedFiles();
        foreach(QString name, fileName){
            if (name.contains("danser")){
                return name;
            }
        }
    }
    return nullptr;
}

bool MainWindow::scanFolder(){
    QDir dir;
    QRegExp exp("danser*.exe");
    exp.setPatternSyntax(QRegExp::Wildcard);
    QStringList strList = dir.entryList();
    path = dir;
    foreach (QString fileName, strList) {
        if(exp.exactMatch(fileName)){
            appName = fileName.toStdString();
            return true;
        }
    }
    return false;
}
String MainWindow::buildCommand(){
    String res;
    res = "\"" + appName + "\"" + " -title=" + "\"" + songName + "\" " + "-difficulty=" + "\"" + difficulty + "\" ";
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
bool MainWindow::getExit(){
    return exPr;
}


void MainWindow::onAnyClick(){
    this->difficulty = ui->cSongDifficulty->currentText().toStdString();
    this->songName = ui->SongSelection->currentText().toStdString();
    if (songName.empty() || difficulty.empty()){
        ui->start->setEnabled(false);
    }else{
        ui->start->setEnabled(true);
    }

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

void MainWindow::setDir(QDir dir){
    path = dir;
}

void MainWindow::setExit(bool boolean){
    exPr = boolean;
}

void MainWindow::on_update_clicked()
{
    ui->cSongDifficulty->clear();
    ui->SongSelection->clear();
    String cd = "cd \"" + getDir().path().toStdString() + "\"";
    String cmd = appName + " -title=\"F\"";
    pr.execute(QString::fromStdString(cd));
    qDebug() << pr.isOpen();
    pr.execute(QString::fromStdString(cmd));
    setSongs();
}

void MainWindow::on_start_clicked()
{
    onAnyClick();
    if (!appName.empty()){
        qDebug() << QString::fromStdString(buildCommand());
        if(pr.execute(QString::fromStdString(buildCommand()))){
            qDebug() << "Ok";
            pr.waitForFinished();
        }
    }
}

void MainWindow::on_SongSelection_activated(const QString &arg1)
{
    ui->cSongDifficulty->clear();
    std::vector<QString> difficulties = sql.getDifficulty(arg1);
    for (auto it : difficulties){
        ui->cSongDifficulty->addItem(it);
    }
    onAnyClick();

}

void MainWindow::on_cSongDifficulty_activated(const QString &arg1)
{
    (void) arg1;
    onAnyClick();
}
