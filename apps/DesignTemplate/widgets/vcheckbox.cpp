#include "vcheckbox.h"

VCheckBox::VCheckBox(QWidget *parent) :
    QCheckBox(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
}

VCheckBox::~VCheckBox()
{
}

//void VCheckBox::mouseReleaseEvent(QMouseEvent *)
//{
//    emit mouseReleased();
//}

void VCheckBox::hoverEnter(QHoverEvent *)
{
    setCursor(Qt::PointingHandCursor);

    setStyleSheet("color:#00aaff;");

    emit mouseHovered();
}

void VCheckBox::hoverLeave(QHoverEvent *)
{
    setCursor(Qt::ArrowCursor);

    setStyleSheet("color:#000000;");

    emit mouseLeaved();
}

void VCheckBox::hoverMove(QHoverEvent *)
{
    setCursor(Qt::PointingHandCursor);

    setStyleSheet("color:#00aaff;");

    emit mouseHovered();
}

bool VCheckBox::event(QEvent *event)
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
