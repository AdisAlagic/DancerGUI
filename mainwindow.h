#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "sqlitemanager.h"

#include <string>
#include <map>
#include <qdir.h>
typedef  std::string String;
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool getExit();
    QDir getDir();
    void setDir(QDir dir);
    void setExit(bool boolean);
    ~MainWindow();

private slots:

    void on_cursor_valueChanged(const QString &arg1);

    void on_tag_valueChanged(const QString &arg1);

    void on_pitch_valueChanged(const QString &arg1);

    void on_sittings_valueChanged(const QString &arg1);

    void on_mover_currentTextChanged(const QString &arg1);

    void on_fps_stateChanged(int arg1);

    void on_debug_stateChanged(int arg1);

    void on_speed_valueChanged(const QString &arg1);

    void on_update_clicked();

    void on_start_clicked();

    void on_SongSelection_activated(const QString &arg1);

    void on_cSongDifficulty_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;
    String command;
    String appName;
    String songName;
    String difficulty;
    String mover;

    int cursors;
    int tag;
    double speed;
    double pitch;
    int sittings;
    QDir path;

    bool exPr;
    bool fps;
    bool debug;

    QProcess pr;
    SQLiteManager sql;
    void setSongs();
    void onAnyClick();
    void copySittings();
    QString openFile();
    String buildCommand();
    bool scanFolder();
    QStringList getArgs();
};
#endif // MAINWINDOW_H
