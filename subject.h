#ifndef SUBJECT_H
#define SUBJECT_H

#include <QWidget>
#include <QDrag>
#include <QPixmap>
#include <QPaintEvent>
#include <QMimeData>

namespace Ui {
class subject;
}

class subject : public QWidget
{
    Q_OBJECT

public:
    explicit subject(QWidget *parent = nullptr);
    ~subject();

    void create(int a, int b, QWidget *widget);
    void setMimeData(QString data);
    void setID(int ID);
    int getID();
    void setRowCol(int row, int col);

    QDrag *makeDrag();

protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::subject *ui;
    QString m_mimeData;
    int m_ID;
    int m_row;
    int m_col;
    QPixmap m_pixmap;
    QPoint m_dragStart;
};

#endif // SUBJECT_H
