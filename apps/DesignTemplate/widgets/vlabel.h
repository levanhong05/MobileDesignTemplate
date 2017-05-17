#ifndef VLABEL_H
#define VLABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>

#include <QEvent>
#include <QMouseEvent>
#include <QHoverEvent>

class VLabel : public QLabel
{
    Q_OBJECT
public:
    explicit VLabel(QWidget *parent = 0);
    ~VLabel();

    void mouseReleaseEvent(QMouseEvent *);

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

#endif // VLABEL_H
