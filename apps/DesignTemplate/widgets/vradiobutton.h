#ifndef VRADIOBUTTON_H
#define VRADIOBUTTON_H

#include <QObject>
#include <QWidget>
#include <QRadioButton>

#include <QEvent>
#include <QMouseEvent>
#include <QHoverEvent>

class VRadioButton : public QRadioButton
{
    Q_OBJECT
public:
    explicit VRadioButton(QWidget *parent = 0);
    ~VRadioButton();

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

#endif // VRADIOBUTTON_H
