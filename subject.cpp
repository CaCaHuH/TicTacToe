#include "subject.h"
#include "ui_subject.h"
#include <QVariant>
#include <QMouseEvent>
#include <QPainter>

subject::subject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subject)
{
    ui->setupUi(this);
}

subject::~subject()
{
    delete ui;
}

void subject::create(int a, int b, QWidget *widget)
{
    widget->setMinimumHeight(a);
    widget->setMinimumWidth(b);
}

void subject::setMimeData(QString data)
{
    m_mimeData = data;
}

void subject::setID(int ID)
{
    m_ID = ID;
    if (m_ID == 0) m_pixmap.load("krestik.png");
    else if (m_ID == 1) m_pixmap.load("nolik.png");
    else if (m_ID == 2) m_pixmap.load("krestik_active.png");
    else if (m_ID == 3) m_pixmap.load("nolik_active.png");
    else m_pixmap.load("");
}

int subject::getID()
{
    return m_ID;
}

void subject::setRowCol(int row, int col)
{
    m_row = row;
    m_col = col;
}

QDrag *subject::makeDrag()
{
    QDrag *drag = new QDrag(this);
    QByteArray itemData;
    QDataStream stream(&itemData, QIODevice::WriteOnly);
    stream << m_row << m_col << m_ID;
    QMimeData *mimedata = new QMimeData;
    mimedata->setData(m_mimeData, itemData);
    drag->setMimeData(mimedata);
    drag->setPixmap(m_pixmap.scaled(size(),Qt::KeepAspectRatio));
    return drag;
}

void subject::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void subject::mousePressEvent(QMouseEvent *event)
{
    m_dragStart = event->pos();
    QWidget::mousePressEvent(event);
}

void subject::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && QApplication::startDragDistance() <= (event->pos() - m_dragStart).manhattanLength())
    {
        makeDrag()->exec(Qt::MoveAction);
    }
    QWidget::mouseMoveEvent(event);
}

void subject::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (!m_pixmap.isNull())
    {
        QSize widgetSize = size();
        QPixmap scalePixmap = m_pixmap.scaled(widgetSize, Qt::KeepAspectRatio);
        QPoint center((widgetSize.width() - scalePixmap.width())/2, (widgetSize.height() - scalePixmap.height())/2);
        painter.drawPixmap(center, scalePixmap);
    }
    QWidget::paintEvent(event);
}

