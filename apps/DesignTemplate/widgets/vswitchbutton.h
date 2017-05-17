#ifndef VSWITCHBUTTON_H
#define VSWITCHBUTTON_H

#include <QtWidgets>

class VSwitchButton : public QAbstractButton
{
    Q_OBJECT
    Q_PROPERTY(int offset READ offset WRITE setOffset)
public:
    VSwitchButton(QWidget *parent = 0);
    VSwitchButton(const QBrush &brush, QWidget *parent = 0);

    QSize sizeHint() const override;

    QBrush brush() const {
        return _brush;
    }
    void setBrush(const QBrush &brsh) {
        _brush = brsh;
    }

    int offset() const {
        return _x;
    }
    void setOffset(int o) {
        _x = o;
        update();
    }

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void enterEvent(QEvent *) override;

signals:
    void onStateChanged(bool state);

private:
    bool _switch;
    QString _text;
    qreal _opacity;
    int _x, _y, _height, _margin;
    QBrush _thumb, _track, _brush;
    QPropertyAnimation *_anim = nullptr;
};

#endif // VSWITCHBUTTON_H
