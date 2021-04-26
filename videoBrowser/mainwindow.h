#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDirIterator>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setRootDirectory(QString path);

public slots:
    void changeDir();
private:
    void resizeEvent(QResizeEvent* event);
    void keyPressEvent(QKeyEvent* event);
    Ui::MainWindow *ui;
    QMediaPlayer *player_;
    QVideoWidget *vw_;
    QDirIterator *it_;
    QVector<QString> dirs_;
    unsigned int currentDirIndex_;
    unsigned int multiplier_;
    QMediaPlaylist *playlist_;


};
#endif // MAINWINDOW_H
