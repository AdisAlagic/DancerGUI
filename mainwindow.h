#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <string>
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
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_SongSelection_currentTextChanged(const QString &arg1);

    void on_cSongDifficulty_currentTextChanged(const QString &arg1);

    void on_cursor_valueChanged(const QString &arg1);

    void on_tag_valueChanged(const QString &arg1);

    void on_pitch_valueChanged(const QString &arg1);

    void on_sittings_valueChanged(const QString &arg1);

    void on_mover_currentTextChanged(const QString &arg1);

    void on_fps_stateChanged(int arg1);

    void on_debug_stateChanged(int arg1);

    void on_speed_valueChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    String command;
    String appName;
    String songName;
    String difficuty;
    String mover;

    int cursors;
    int tag;
    double speed;
    double pitch;
    int sittings;

    bool fps;
    bool debug;

    void onAnyClick();
    String buildCommand();
};
#endif // MAINWINDOW_H
