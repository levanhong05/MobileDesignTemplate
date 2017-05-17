#include "vtoolbutton.h"

VToolButton::VToolButton(QWidget *parent) :
    QToolButton(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
}

VToolButton::~VToolButton()
{
}

//void VToolButton::mouseReleaseEvent(QMouseEvent *)
//{
//    emit mouseReleased();
//}

void VToolButton::hoverEnter(QHoverEvent *)
{
    setCursor(Qt::PointingHandCursor);

    emit mouseHovered();
}

void VToolButton::hoverLeave(QHoverEvent *)
{
    setCursor(Qt::ArrowCursor);

    emit mouseLeaved();
}

void VToolButton::hoverMove(QHoverEvent *)
{
    setCursor(Qt::PointingHandCursor);

    emit mouseHovered();
}

bool VToolButton::event(QEvent *event)
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
