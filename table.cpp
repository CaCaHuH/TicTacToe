#include "table.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include "subject.h"
#include <QDebug>
#include <QHeaderView>

table::table()
{
    setAcceptDrops(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    lastID = 1;
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);
    setMinimumHeight(302);
    setMinimumWidth(302);
    for (int i = 0; i < 9; i++)
    {
        posTable[i] = 2;
    }
}

QVector<DataTable> table::getData()
{
    QVector<DataTable> result;
    for (int i = 0; i < model()->rowCount(); i++)
    {
        for (int j = 0; j < model()->columnCount(); j++)
        {
            auto ptr = cellWidget(i,j);
            if (ptr != nullptr)
            {
                subject *subinTable = static_cast<subject*>(ptr);
                DataTable data;
                data.row = i;
                data.col = j;
                data.ID = subinTable->getID();
                data.lastID = lastID;
                data.stopDrop = stopDrop;
                result.push_back(data);
            }
        }
    }
    return result;
}

void table::setData(QVector<DataTable> &data)
{
    lastID = data[1].lastID;
    stopDrop = data[1].stopDrop;
    for (int i = 0; i < model()->rowCount(); i++)
    {
        for (int j = 0; j < model()->columnCount(); j++)
        {
            auto ptr = cellWidget(i,j);
            if (ptr != nullptr)
            {
                removeCellWidget(i,j);
            }
        }
    }
    for (int i = 0; i < data.size(); i++)
    {
        subject *subinTable = new subject();
        subinTable->create(100,100,subinTable);
        subinTable->setMimeData("aplication/subjectInTable");
        subinTable->setRowCol(data[i].row,data[i].col);
        subinTable->setID(data[i].ID);
        setCellWidget(data[i].row,data[i].col,subinTable);
    }
}

void table::removeStopDrop()
{
    stopDrop = 0;
}

void table::dragEnterEvent(QDragEnterEvent* event)
{
    int m_row, m_col;
    QByteArray DATA = event->mimeData()->data("aplication/subject");
    QDataStream stream(&DATA, QIODevice::ReadOnly);
    stream >> m_row >> m_col >> nowID;

    if(event->mimeData()->hasFormat("aplication/subject") && lastID != nowID && stopDrop == 0)
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void table::dropEvent(QDropEvent* event)
{
    QModelIndex indexCur = indexAt(event->pos());
    if(!indexCur.isValid()) return;

    handleSubject(event,indexCur.row(),indexCur.column());
}

void table::clearTable()
{
    for (int i = 0; i < model()->rowCount(); i++)
    {
        for (int j = 0; j < model()->columnCount(); j++)
        {
            auto ptr = cellWidget(i,j);
            if (ptr != nullptr)
            {
                removeCellWidget(i,j);
            }
        }
    }
    for (int i = 0; i < 9; i++)
    {
        posTable[i] = 2;
    }
}

int table::getInfoMatch()
{
    return infoMatch;
}

void table::removeInfoMatch()
{
    infoMatch = 0;
}

void table::removeLastID()
{
    lastID = 1;
}

void table::handleSubject(QDropEvent *event, int rowto, int colto)
{
    QByteArray data = event->mimeData()->data("aplication/subject");
    QDataStream in(&data, QIODevice::ReadOnly);
    int row;
    int col;
    int ID;
    in >> row >> col >> ID;

    auto ptr = cellWidget(rowto,colto);
    if (ptr == nullptr)
    {
        subject *subinTable = new subject();
        subinTable->create(100,100,subinTable);
        subinTable->setMimeData("aplication/subjectInTable");
        subinTable->setRowCol(rowto,colto);
        subinTable->setID(ID);
        setCellWidget(rowto,colto,subinTable);
        lastID = nowID;
    }
    checkMatch();
}

void table::checkMatch()
{
    for (int i = 0; i < model()->rowCount(); i++)
    {
        for (int j = 0; j < model()->columnCount(); j++)
        {
            auto ptr = cellWidget(i,j);
            if (ptr != nullptr)
            {
                subject *subinTable = static_cast<subject*>(ptr);
                posTable[i*3 + j] = subinTable->getID();
            }
        }
    }
    if ((posTable[0] == 0 && posTable[1] == 0 && posTable[2] == 0)||(posTable[0] == 1 && posTable[1] == 1 && posTable[2] == 1))
    {
        if (posTable[0] == 0) infoMatch = paintLine(0, 1, 2, 0);
        else infoMatch = paintLine(0, 1, 2, 1);
        lastID = 1;
        stopDrop = 1;
    }
    else if ((posTable[3] == 0 && posTable[4] == 0 && posTable[5] == 0)||(posTable[3] == 1 && posTable[4] == 1 && posTable[5] == 1))
    {
        if (posTable[3] == 0) infoMatch = paintLine(3, 4, 5, 0);
        else infoMatch = paintLine(3, 4, 5, 1);
        lastID = 1;
        stopDrop = 1;
    }
    else if ((posTable[6] == 0 && posTable[7] == 0 && posTable[8] == 0)||(posTable[6] == 1 && posTable[7] == 1 && posTable[8] == 1))
    {
        if (posTable[6] == 0) infoMatch = paintLine(6, 7, 8, 0);
        else infoMatch = paintLine(6, 7, 8, 1);
        lastID = 1;
        stopDrop = 1;
    }
    else if ((posTable[0] == 0 && posTable[3] == 0 && posTable[6] == 0)||(posTable[0] == 1 && posTable[3] == 1 && posTable[6] == 1))
    {
        if (posTable[0] == 0) infoMatch = paintLine(0, 3, 6, 0);
        else infoMatch = paintLine(0, 3, 6, 1);
        lastID = 1;
        stopDrop = 1;
    }
    else if ((posTable[1] == 0 && posTable[4] == 0 && posTable[7] == 0)||(posTable[1] == 1 && posTable[4] == 1 && posTable[7] == 1))
    {
        if (posTable[1] == 0) infoMatch = paintLine(1, 4, 7, 0);
        else infoMatch = paintLine(1, 4, 7, 1);
        lastID = 1;
        stopDrop = 1;
    }
    else if ((posTable[2] == 0 && posTable[5] == 0 && posTable[8] == 0)||(posTable[2] == 1 && posTable[5] == 1 && posTable[8] == 1))
    {
        if (posTable[2] == 0) infoMatch = paintLine(2, 5, 8, 0);
        else infoMatch = paintLine(2, 5, 8, 1);
        lastID = 1;
        stopDrop = 1;
    }
    else if ((posTable[0] == 0 && posTable[4] == 0 && posTable[8] == 0)||(posTable[0] == 1 && posTable[4] == 1 && posTable[8] == 1))
    {
        if (posTable[0] == 0) infoMatch = paintLine(0, 4, 8, 0);
        else infoMatch = paintLine(0, 4, 8, 1);
        lastID = 1;
        stopDrop = 1;
    }
    else if ((posTable[2] == 0 && posTable[4] == 0 && posTable[6] == 0)||(posTable[2] == 1 && posTable[4] == 1 && posTable[6] == 1))
    {
        if (posTable[2] == 0) infoMatch = paintLine(2, 4, 6, 0);
        else infoMatch = paintLine(2, 4, 6, 1);
        lastID = 1;
        stopDrop = 1;
    }

    int sum = 0;
    for (int i = 0; i < 9; i++)
    {
        if (posTable[i] == 2) sum++;
    }
    if (sum == 0)
    {
        lastID = 1;
        stopDrop = 1;
    }
}

int table::paintLine(int one, int two, int three, int ID)
{
    int j = one%3;
    int i = (one - j)/3;
    auto ptr = cellWidget(i,j);
    subject *subinTable = static_cast<subject*>(ptr);
    subinTable->setID(ID+2);

    j = two%3;
    i = (two - j)/3;
    ptr = cellWidget(i,j);
    subinTable = static_cast<subject*>(ptr);
    subinTable->setID(ID+2);

    j = three%3;
    i = (three - j)/3;
    ptr = cellWidget(i,j);
    subinTable = static_cast<subject*>(ptr);
    subinTable->setID(ID+2);

    return ID+1;
}
