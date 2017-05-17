#ifndef VPUSHBUTTON_H
#define VPUSHBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

#include <QEvent>
#include <QMouseEvent>
#include <QHoverEvent>

class VPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit VPushButton(QWidget *parent = 0);
    ~VPushButton();

    //void mouseReleaseEvent(QMouseEvent *);

protected:
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void hoverMove(QHoverEvent *event);
    bool event(QEvent *event);

signals:
    void mouseHovered();

    void mouseReleased();

    void mouseLeaved();
};

#endif // VPUSHBUTTON_H
