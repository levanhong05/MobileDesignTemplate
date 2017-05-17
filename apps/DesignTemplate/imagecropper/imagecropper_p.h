#ifndef IMAGECROPPER_P_H
#define IMAGECROPPER_P_H

#include "imagecropper_e.h"

#include <QtCore/QRect>
#include <QtGui/QPixmap>
#include <QtGui/QColor>

namespace {
    const QRect INIT_CROPPING_RECT = QRect();
    const QSizeF INIT_PROPORTION = QSizeF(1.0, 1.0);
}

class ImageCropperPrivate {
public:
    ImageCropperPrivate() :
        imageForCropping(QPixmap()),
        croppingRect(INIT_CROPPING_RECT),
        lastStaticCroppingRect(QRect()),
        cursorPosition(CursorPositionUndefined),
        isMousePressed(false),
        isProportionFixed(false),
        startMousePos(QPoint()),
        proportion(INIT_PROPORTION),
        deltas(INIT_PROPORTION),
        backgroundColor(Qt::black),
        croppingRectBorderColor(Qt::white)
    {}

public:
    // Trimming image
    QPixmap imageForCropping;
    // Trimming area
    QRectF croppingRect;
    // Last fixed trimming area
    QRectF lastStaticCroppingRect;
    // The cursor position relative to the cropping area
    CursorPosition cursorPosition;
    // Is the left mouse button pressed?
    bool isMousePressed;
    // Fix the proportions of the cropping area
    bool isProportionFixed;
    // Starting position of the cursor when changing the size of the cropping area
    QPointF startMousePos;
    // Proportions
    QSizeF proportion;
    // Increments
    // width  - X increment
    // height - Y increment
    QSizeF deltas;
    // The color of the background fill under the image
    QColor backgroundColor;
    // Crop area border color
    QColor croppingRectBorderColor;
};

#endif // IMAGECROPPER_P_H
