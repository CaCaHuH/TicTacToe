#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void create();

public slots:
    void saveClick();
    void loadClick();
    void newgameClick();

private:
    Ui::MainWindow *ui;
    gamewidget m_widget;
};
#endif // MAINWINDOW_H
