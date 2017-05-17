#include "vswitchbutton.h"

VSwitchButton::VSwitchButton(QWidget *parent) :
    QAbstractButton(parent),
    _height(29),
    _opacity(0.000),
    _switch(false),
    _margin(3),
    _thumb("#d5d5d5"),
    _text(tr("OFF")),
    _anim(new QPropertyAnimation(this, "offset", this))
{
    setOffset(_height / 2);

    _y = _height / 2;

    setBrush(QColor("#009688"));
}

VSwitchButton::VSwitchButton(const QBrush &brush, QWidget *parent) :
    QAbstractButton(parent),
    _height(29),
    _switch(false),
    _opacity(0.000),
    _margin(3),
    _thumb("#d5d5d5"),
    _text(tr("OFF")),
    _anim(new QPropertyAnimation(this, "offset", this))
{
    setOffset(_height / 2);

    _y = _height / 2;

    setBrush(brush);
}

void VSwitchButton::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter p(this);
    p.setPen(Qt::NoPen);

    if (isEnabled()) {
        p.setBrush(_switch ? brush() : Qt::black);
        p.setOpacity(_switch ? 0.5 : 0.38);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.drawRoundedRect(QRect(_margin, _margin, width() - 2 * _margin, height() - 2 * _margin), 8.0, 8.0);
        p.setBrush(_thumb);
        p.setOpacity(1.0);
        p.drawEllipse(QRectF(offset() - (_height / 2), _y - (_height / 2), height(), height()));
    } else {
        p.setBrush(Qt::black);
        p.setOpacity(0.12);
        p.drawRoundedRect(QRect(_margin, _margin, width() - 2 * _margin, height() - 2 * _margin), 8.0, 8.0);
        p.setOpacity(1.0);
        p.setBrush(QColor("#bdbdbd"));
        p.drawEllipse(QRectF(offset() - (_height / 2), _y - (_height / 2), height(), height()));
    }

    p.drawText(0,0, _text);
}

void VSwitchButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() & Qt::LeftButton) {
        _switch = _switch ? false : true;
        _thumb = _switch ? _brush : QBrush("#d5d5d5");

        if (_switch) {
            _anim->setStartValue(_height / 2);
            _anim->setEndValue(width() - _height / 4 * 3);
            _anim->setDuration(120);
            _anim->start();
            _text = tr("ON");
        } else {
            _anim->setStartValue(offset());
            _anim->setEndValue(_height / 2);
            _anim->setDuration(120);
            _anim->start();
            _text = tr("OFF");
        }

        emit onStateChanged(_switch);
    }

    QAbstractButton::mouseReleaseEvent(e);
}

void VSwitchButton::enterEvent(QEvent *e)
{
    setCursor(Qt::PointingHandCursor);

    QAbstractButton::enterEvent(e);
}

QSize VSwitchButton::sizeHint() const
{
    return QSize(2 * (_height + _margin), _height + 2 * _margin);
}
