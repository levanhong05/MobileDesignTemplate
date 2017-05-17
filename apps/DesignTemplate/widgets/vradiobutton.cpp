#include "vradiobutton.h"

VRadioButton::VRadioButton(QWidget *parent) :
    QRadioButton(parent)
{
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover);
}

VRadioButton::~VRadioButton()
{
}

//void VRadioButton::mouseReleaseEvent(QMouseEvent *)
//{
//    emit mouseReleased();
//}

void VRadioButton::hoverEnter(QHoverEvent *)
{
    setCursor(Qt::PointingHandCursor);

    setStyleSheet("color:#00aaff;");

    emit mouseHovered();
}

void VRadioButton::hoverLeave(QHoverEvent *)
{
    setCursor(Qt::ArrowCursor);

    setStyleSheet("color:#000000;");

    emit mouseLeaved();
}

void VRadioButton::hoverMove(QHoverEvent *)
{
    setCursor(Qt::PointingHandCursor);

    setStyleSheet("color:#00aaff;");

    emit mouseHovered();
}

bool VRadioButton::event(QEvent *event)
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
