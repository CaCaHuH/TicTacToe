#ifndef TABLE_H
#define TABLE_H
#include <QTableWidget>

struct DataTable
{
    int ID;
    int row;
    int col;
    int lastID;
    int stopDrop;
};

class table : public QTableWidget
{
public:
    table();

    void removeStopDrop();
    void clearTable();
    int getInfoMatch();
    void removeInfoMatch();
    void removeLastID();

    QVector<DataTable> getData();
    void setData(QVector<DataTable> &data);

protected:
    virtual void dragEnterEvent(QDragEnterEvent* event) override;
    virtual void dropEvent(QDropEvent* event) override;

private:
    void handleSubject(QDropEvent *event, int rowto, int colto);
    void checkMatch();
    int paintLine(int one, int two, int three, int ID);

    int lastID;
    int nowID;
    int posTable[9];
    int infoMatch;
    bool stopDrop;
};

#endif // TABLE_H
