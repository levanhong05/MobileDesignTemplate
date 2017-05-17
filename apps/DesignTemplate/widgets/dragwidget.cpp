#include "dragwidget.h"

#include <QtWidgets>

DragWidget::DragWidget(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    _layout = new QHBoxLayout();
    _layout->setMargin(0);
    _layout->setContentsMargins(0,0,0,0);
    _layout->setSpacing(0);
    setLayout(_layout);

    QLabel *glass1 = new QLabel(this);
    glass1->setPixmap(QPixmap::fromImage(QImage(":/design/images/glass/glass.png")));
    glass1->setScaledContents(true);

    QLabel *glass2 = new QLabel(this);
    glass2->setPixmap(QPixmap::fromImage(QImage(":/design/images/glass/glass.png")));
    glass2->setScaledContents(true);

    QLabel *glass3 = new QLabel(this);
    glass3->setPixmap(QPixmap::fromImage(QImage(":/design/images/glass/glass.png")));
    glass3->setScaledContents(true);

    QLabel *glass4 = new QLabel(this);
    glass4->setPixmap(QPixmap::fromImage(QImage(":/design/images/glass/glass.png")));
    glass4->setScaledContents(true);

    _layout->addWidget(glass1);
    _layout->addWidget(glass2);
    _layout->addWidget(glass3);
    _layout->addWidget(glass4);
}

void DragWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        dataStream >> pixmap >> offset;

        QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        _layout->addWidget(newIcon);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;

    QPixmap pixmap = *child->pixmap();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);

    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
        child->close();
    } else {
        child->show();
        child->setPixmap(pixmap);
    }
}
