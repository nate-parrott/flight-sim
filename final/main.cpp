#include <QApplication>
#include "mainwindow.h"
#include <QDir>
#include "final.h"

#define PATH_TO_DATA_DIR "/Users/nateparrott/Documents/SW/flight-sim/final/data"

QString pathForResource(const char* resource) {
    //return QString(":/data/data/") + QString(resource);
    return QDir(QString(PATH_TO_DATA_DIR)).absoluteFilePath(QString(resource));
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    bool startFullscreen = false;

    w.show();

    if (startFullscreen) {
        // We cannot use w.showFullscreen() here because on Linux that creates the
        // window behind all other windows, so we have to set it to fullscreen after
        // it has been shown.
        w.setWindowState(w.windowState() | Qt::WindowFullScreen);
    }

    return a.exec();
}

