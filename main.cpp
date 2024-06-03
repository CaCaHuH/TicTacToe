#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");
    MainWindow w;
    w.setWindowTitle("Your first game");
    w.show();
    w.create();
    return a.exec();
}
