#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "subject.h"
#include "table.h"

struct DATAGAME
{
    int scorekrestik;
    int scorenolik;
    QVector<DataTable> Data;
};

namespace Ui {
class gamewidget;
}

class gamewidget : public QWidget
{
    Q_OBJECT

public:
    explicit gamewidget(QWidget *parent = nullptr);
    ~gamewidget();

    void create();
    DATAGAME getDataTable();
    void setDataTable(DATAGAME &data);
    void NewGame();

private slots:
    void on_restart_clicked();

private:
    Ui::gamewidget *ui;
    subject m_sub1;
    subject m_sub2;
    table m_table;
};

#endif // GAMEWIDGET_H
