#ifndef VCHECKBOX_H
#define VCHECKBOX_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>

#include <QEvent>
#include <QMouseEvent>
#include <QHoverEvent>

class VCheckBox : public QCheckBox
{
    Q_OBJECT
public:
    explicit VCheckBox(QWidget *parent = 0);
    ~VCheckBox();

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

#endif // VCHECKBOX_H
