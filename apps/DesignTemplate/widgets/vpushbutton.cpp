#include "vpushbutton.h"

VPushButton::VPushButton(QWidget *parent) :
    QPushButton(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
}

VPushButton::~VPushButton()
{
}

//void VPushButton::mouseReleaseEvent(QMouseEvent *)
//{
//    emit mouseReleased();
//}

void VPushButton::hoverEnter(QHoverEvent *)
{
    setCursor(Qt::PointingHandCursor);

    setStyleSheet("color:#00aaff;");

    emit mouseHovered();
}

void VPushButton::hoverLeave(QHoverEvent *)
{
    setCursor(Qt::ArrowCursor);

    setStyleSheet("color:#000000;");

    emit mouseLeaved();
}

void VPushButton::hoverMove(QHoverEvent *)
{
    setCursor(Qt::PointingHandCursor);

    setStyleSheet("color:#00aaff;");

    emit mouseHovered();
}

bool VPushButton::event(QEvent *event)
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

