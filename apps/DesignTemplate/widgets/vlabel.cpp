#include "vlabel.h"

#include <QDebug>

VLabel::VLabel(QWidget *parent) :
    QLabel(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
}

VLabel::~VLabel()
{
}

void VLabel::mouseReleaseEvent(QMouseEvent *)
{
    emit mouseReleased();
}

void VLabel::hoverEnter(QHoverEvent *)
{
    setCursor(Qt::PointingHandCursor);

    setStyleSheet("color:#00aaff;");

    emit mouseHovered();
}

void VLabel::hoverLeave(QHoverEvent *)
{
    setCursor(Qt::ArrowCursor);

    setStyleSheet("color:#000000;");

    emit mouseLeaved();
}

void VLabel::hoverMove(QHoverEvent *)
{
    setCursor(Qt::PointingHandCursor);

    setStyleSheet("color:#00aaff;");

    emit mouseHovered();
}

bool VLabel::event(QEvent *event)
{
    switch(event->type()) {
        case QEvent::HoverEnter:
            hoverEnter(static_cast<QHoverEvent*>(event));
            return true;
            break;
        case QEvent::HoverLeave:
            hoverLeave(static_cast<QHoverEvent*>(event));
            return true;
            break;
        case QEvent::HoverMove:
            hoverMove(static_cast<QHoverEvent*>(event));
            return true;
            break;
        default:
            break;
    }

    return QWidget::event(event);
}
