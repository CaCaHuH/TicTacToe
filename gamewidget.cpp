#include "gamewidget.h"
#include "ui_gamewidget.h"
#include <QPixmap>

gamewidget::gamewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewidget)
{
    ui->setupUi(this);
    connect(ui->restart,SIGNAL(clicked()),this,SLOT(on_restart_clicked()));
}

gamewidget::~gamewidget()
{
    delete ui;
}

void gamewidget::create()
{
    m_sub1.create(100,100,&m_sub1);
    m_sub1.setID(0);
    ui->widgetswindow->addWidget(&m_sub1);
    m_sub1.setMimeData("aplication/subject");
    m_sub1.setRowCol(-1,-1);

    m_sub2.create(100,100,&m_sub2);
    m_sub2.setID(1);
    ui->widgetswindow->addWidget(&m_sub2);
    m_sub2.setMimeData("aplication/subject");
    m_sub2.setRowCol(-1,-1);

    ui->tablewindow->addWidget(&m_table);
    m_table.setRowCount(3);
    m_table.setColumnCount(3);
    m_table.setRowHeight(0,100);
    m_table.setRowHeight(1,100);
    m_table.setRowHeight(2,100);
    m_table.setColumnWidth(0,100);
    m_table.setColumnWidth(1,100);
    m_table.setColumnWidth(2,100);

    QPixmap pix1;
    pix1.load("C:/krestik.png");
    ui->iconkrestik->setPixmap(pix1);
    pix1.load("C:/nolik.png");
    ui->iconnolik->setPixmap(pix1);
}

DATAGAME gamewidget::getDataTable()
{
    DATAGAME data;
    data.scorekrestik = ui->scorekrestik->text().toInt();
    data.scorenolik = ui->scorenolik->text().toInt();
    data.Data = m_table.getData();
    return data;
}

void gamewidget::setDataTable(DATAGAME &data)
{
    QString str = QString::number(data.scorekrestik);
    ui->scorekrestik->setText(str);
    str = QString::number(data.scorenolik);
    ui->scorenolik->setText(str);
    m_table.setData(data.Data);
}

void gamewidget::NewGame()
{
    ui->scorekrestik->setText("0");
    ui->scorenolik->setText("0");
    m_table.clearTable();
    m_table.removeStopDrop();
    m_table.removeInfoMatch();
    m_table.removeLastID();
}

void gamewidget::on_restart_clicked()
{
    m_table.removeStopDrop();
    m_table.clearTable();
    int info = m_table.getInfoMatch();
    int counter;
    QString str;
    if (info == 1)
    {
        counter = ui->scorekrestik->text().toInt();
        counter++;
        str = QString::number(counter);
        ui->scorekrestik->setText(str);
    }
    else if (info == 2)
    {
        counter = ui->scorenolik->text().toInt();
        counter++;
        str = QString::number(counter);
        ui->scorenolik->setText(str);
    }
    m_table.removeInfoMatch();
    m_table.removeLastID();
}
