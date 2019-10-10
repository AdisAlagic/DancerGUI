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
        copySittings();
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
    qDebug() << QString::fromStdString(appName).split("/").back();
    pr.setProgram(QString::fromStdString(appName).split("/").back());
    pr.setWorkingDirectory(getDir().path());
    pr.setArguments(getArgs());
    on_update_clicked();
    }
}
/**
 * @brief MainWindow::setSongs
 * Adds songs into the combobox from DataBase
 */
void MainWindow::setSongs(){
    std::vector<QString> songs = sql.getSongs(getDir().path());
    for (auto it : songs){
        ui->SongSelection->addItem(it);
    }

}

QDir MainWindow::getDir(){
    //qDebug() << path.path();
    return path;
}

/**
 * @brief MainWindow::openFile
 * @return Name of the file with full path
 * Opens diolog with file selection, checks for name "danser"
 */
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
/**
 * @brief MainWindow::scanFolder
 * @return true if found
 * Scans folder for executable file danser
 */
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
/**
 * @brief MainWindow::buildCommand
 * @return command for launch
 * Builds command for danser to launch
 */
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


QStringList MainWindow::getArgs(){
    QStringList args;
    if (cursors != 0){
       args.push_front(" -cursors=" + QString(cursors));
    }
    if (pitch != 0.0){
       args.push_front( " -pitch=" + QString::fromStdString(std::to_string(pitch)));
    }
    if (speed != 0.0){
       args.push_front(" -speed=" + QString::fromStdString(std::to_string(speed)));
    }
    if (tag != 0){
       args.push_front( " -tag=" + QString::fromStdString(std::to_string(tag)));
    }
    if (sittings != 0){
        args.push_front( " -sittings=" + QString::fromStdString(std::to_string(sittings)));
    }
    if (mover != "flower"){
        args.push_front(" -mover=" + QString::fromStdString(mover));
    }
    if (fps){
        args.push_front(" -fps");
    }
    if (debug){
        args.push_front(" -debug");
    }

}

bool MainWindow::getExit(){
    return exPr;
}

/**
 * @brief MainWindow::onAnyClick
 * Initializes vars on any click user made.
 */
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

/**
 * @brief MainWindow::on_update_clicked
 * Refreshes list of songs in combobox by updating database and reading it again
 */
void MainWindow::on_update_clicked()
{
    ui->cSongDifficulty->clear();
    ui->SongSelection->clear();
    QStringList fake;
    fake = pr.arguments();
    for (auto it: fake){
        qDebug() << it;
    }
    fake.push_front(" -title=\"F\"");
    pr.setArguments(fake);
    pr.start();
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


void MainWindow::copySittings(){
    foreach(QString file, getDir().entryList()){
        qDebug() << getDir().path();
        if(file.contains("settings")){
            qDebug() << "To " + QDir::current().path() + " from " + getDir().path();
            if(!QFile::copy(getDir().path() + "/" + file, QDir::current().path() + "/" + file)){

                QMessageBox f("Error!", "Error coping sittings. Programm can work incorrect. Or it already exist in the folder", QMessageBox::NoIcon, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
                f.exec();
            }
        }
    }
}
