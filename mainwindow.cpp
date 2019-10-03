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
    ui->pushButton->setEnabled(false);
    if (!scanFolder()){
    tryAgain:
    QMessageBox box("Dancer not found", "Dancer not found, would you like to select exe file?", QMessageBox::Warning, QMessageBox::Yes, QMessageBox::Retry, QMessageBox::No);
    int reply = box.exec();
    switch(reply){
    case QMessageBox::Yes:
        appName = openFile().toStdString();
        if (appName.empty()){
            goto tryAgain;
        }
        break;
    case QMessageBox::No:
        MainWindow::exPr = true;
        QApplication::closeAllWindows();
        break;
    case QMessageBox::Retry:
        if(!scanFolder()){
            goto tryAgain;
        }
    }
    MainWindow::exPr = false;
    }
}

void MainWindow::setSongs(){
    for(auto it: SQLiteManager::songs)
    {
        ui->SongSelection->addItem(it.first.toString());
        ui->cSongDifficulty->addItem(it.second.toString());
    }

}

QDir MainWindow::getDir(){
    return MainWindow::path;
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
bool MainWindow::getExit(){
    return MainWindow::exPr;
}
void MainWindow::onAnyClick(){
    this->difficuty = ui->cSongDifficulty->currentText().toStdString();
    this->songName = ui->SongSelection->currentText().toStdString();
    if (songName.empty() || difficuty.empty()){
        ui->pushButton->setEnabled(false);
    }else{
        ui->pushButton->setEnabled(true);
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
    SQLiteManager::getData();
    setSongs();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    onAnyClick();
    if (!appName.empty()){
        system(buildCommand().c_str());
    }
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


