#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    player_(),
    vw_(),
    it_(),
    dirs_(),
    currentDirIndex_(0),
    multiplier_(1),
    playlist_(new QMediaPlaylist),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player_ = new QMediaPlayer(this);

    vw_ = new QVideoWidget(this);
    player_->setVideoOutput(vw_);

    playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setRootDirectory(QString path)
{
    it_ = new QDirIterator(path);
    while(it_->hasNext())
    {
        dirs_.append(it_->next());
    }
}

void MainWindow::changeDir()
{
    QString currentDir = dirs_.at(currentDirIndex_);
    setWindowTitle(currentDir);

    qDebug() << "currendDirIndex_: " + QString::number(currentDirIndex_) + currentDir;
    QDirIterator it(currentDir, {"*.webm", "*.mp4"}, QDir::Files);
    playlist_->clear();
    while(it.hasNext())
    {
        playlist_->addMedia(QUrl::fromLocalFile(it.next()));
    }
    //playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    player_->setPlaylist(playlist_);
    player_->play();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    vw_->resize(this->width(), this->height());
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "dirs_.size: " + QString::number(dirs_.size());


    if(event->key()==Qt::Key_D)
    {
        playlist_->setPlaybackMode(QMediaPlaylist::Sequential);
        playlist_->next();
        playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        player_->play();
    }
    if(event->key()==Qt::Key_A)
    {
        playlist_->setPlaybackMode(QMediaPlaylist::Sequential);
        playlist_->previous();
        playlist_->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        player_->play();
    }
    if(event->key()==Qt::Key_Q)
    {
        if(multiplier_>1)
        {
            multiplier_ /= 10;
        }
    }
    if(event->key()==Qt::Key_W)
    {
        if(currentDirIndex_>multiplier_)
        {
            qDebug() << "dir--";
            currentDirIndex_ -= multiplier_;
        }
        changeDir();
    }
    if(event->key()==Qt::Key_E)
    {
        if(multiplier_==1)
        {
            multiplier_ = 10;
        }else if(multiplier_<1000)
        {
            multiplier_ *= 10;
        }
        qDebug() << QString::number(multiplier_);
    }
    if(event->key()==Qt::Key_S)
    {
        if(currentDirIndex_+multiplier_<dirs_.size())
        {
            qDebug() << "dir++";
            currentDirIndex_ += multiplier_;
        }
        changeDir();
    }


    QMainWindow::keyPressEvent(event);
}

