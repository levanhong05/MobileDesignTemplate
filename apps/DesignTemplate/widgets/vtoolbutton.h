#ifndef VTOOLBUTTON_H
#define VTOOLBUTTON_H

#include <QObject>
#include <QWidget>
#include <QToolButton>

#include <QEvent>
#include <QMouseEvent>
#include <QHoverEvent>

class VToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit VToolButton(QWidget *parent = 0);
    ~VToolButton();

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

#endif // VTOOLBUTTON_H
