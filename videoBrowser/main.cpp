#include "mainwindow.h"

#include <QApplication>
#include <QFileDialog>
#include <QDirIterator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString path = QFileDialog::getExistingDirectory();
    w.setRootDirectory(path);
    return a.exec();
}
