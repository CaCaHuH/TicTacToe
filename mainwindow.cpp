#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui = new Ui::MainWindow;
    ui->setupUi(this);
    connect(ui->save,SIGNAL(triggered()),this,SLOT(saveClick()));
    connect(ui->load,SIGNAL(triggered()),this,SLOT(loadClick()));
    connect(ui->newgame,SIGNAL(triggered()),this,SLOT(newgameClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::create()
{
    m_widget.create();
    setCentralWidget(&m_widget);
    setMinimumWidth(426);
}

void MainWindow::saveClick()
{
    QString filename = QFileDialog::getSaveFileName(this,"Сохранить игру","tictactoe.txt","*.txt");
    if (filename.isEmpty()) return;
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        DATAGAME data = m_widget.getDataTable();
        for (int i = 0; i < data.Data.size(); i++)
        {
            stream  << data.scorekrestik << ";"
                    << data.scorenolik << ";"
                    << data.Data[i].ID << ";"
                    << data.Data[i].row << ";"
                    << data.Data[i].col << ";"
                    << data.Data[i].lastID << ";"
                    << data.Data[i].stopDrop << "\n";
        }
        file.close();
    }
    else qDebug() << "Can not open file";
}

void MainWindow::loadClick()
{
    QString filename = QFileDialog::getOpenFileName(this,"Загрузить игру","tictactoe.txt","*.txt");
    if (filename.isEmpty()) return;
    QFile file(filename);
    DATAGAME data;
    QVector<DataTable> Data;
    if (file.open(QIODevice::ReadOnly))
    {
        while (!file.atEnd())
        {
            QString line = QString::fromUtf8(file.readLine());
            QStringList tokens = line.split(";");
            auto tokenVector = tokens.toVector();
            if (tokenVector.size() != 7)
            {
                qDebug() << "Error. tokenVector.size() = " << tokenVector.size();
                continue;
            }
            data.scorekrestik = tokenVector[0].toInt();
            data.scorenolik = tokenVector[1].toInt();
            DataTable dataTable;
            dataTable.ID = tokenVector[2].toInt();
            dataTable.row = tokenVector[3].toInt();
            dataTable.col = tokenVector[4].toInt();
            dataTable.lastID = tokenVector[5].toInt();
            dataTable.stopDrop = tokenVector[6].toInt();
            Data.push_back(dataTable);
            data.Data = Data;
        }
        file.close();
    }
    m_widget.setDataTable(data);
}

void MainWindow::newgameClick()
{
    m_widget.NewGame();
}

