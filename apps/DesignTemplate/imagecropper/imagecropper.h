#ifndef IMAGECROPPER_H
#define IMAGECROPPER_H

#include "imagecropper_p.h"
#include "imagecropper_e.h"

#include <QWidget>

class ImageCropper : public QWidget
{
    Q_OBJECT
public:
    ImageCropper(QWidget *parent = 0);
    ~ImageCropper();

public slots:
    // Set the image for cropping
    void setImage(const QPixmap& _image);
    // Set the background color of the crop widget
    void setBackgroundColor(const QColor& _backgroundColor);
    // Set the border color of the cropping area
    void setCroppingRectBorderColor(const QColor& _borderColor);
    // Set the proportions of the selection area
    void setProportion(const QSizeF& _proportion);
    // Use fixed proportions of the selection area
    void setProportionFixed(const bool _isFixed);

public:
    // Crop image
    const QPixmap cropImage();

protected:
    virtual void paintEvent(QPaintEvent* _event);
    virtual void mousePressEvent(QMouseEvent* _event);
    virtual void mouseMoveEvent(QMouseEvent* _event);
    virtual void mouseReleaseEvent(QMouseEvent* _event);

private:
    // Determining the location of the cursor over the widget
    CursorPosition cursorPosition(const QRectF& _cropRect, const QPointF& _mousePosition);
    // Update cursor icon corresponding to mouse location
    void updateCursorIcon(const QPointF& _mousePosition);

    // Get the size of the widget after it is changed by the mouse
    // --------
    // Contracts:
    // 1. The method should be called, only when the mouse button is pressed
    // (ie when moving or resizing a widget)
    // --------
    // In case of failure, returns a null-rectangle
    const QRectF calculateGeometry(
            const QRectF& _sourceGeometry,
            const CursorPosition _cursorPosition,
            const QPointF& _mouseDelta
            );
    // Get the size of the widget after it is changed by the mouse
    // The method changes the widget without preserving the initial proportions of the sides
    // ------
    // Contracts:
    // 1. The method should be called, only when the mouse button is pressed
    // (ie when moving or resizing a widget)
    const QRectF calculateGeometryWithCustomProportions(
            const QRectF& _sourceGeometry,
            const CursorPosition _cursorPosition,
            const QPointF& _mouseDelta
            );
    // Get the size of the widget after it is changed by the mouse
    // The method changes the widget preserving the initial proportions of the sides
    // ------
    // Contracts:
    // 1. The method should be called, only when the mouse button is pressed
    // (ie when moving or resizing a widget)
    const QRectF calculateGeometryWithFixedProportions(const QRectF &_sourceGeometry,
                                                 const CursorPosition _cursorPosition,
                                                 const QPointF &_mouseDelta,
                                                 const QSizeF &_deltas
                                                 );

private:
    // Private data implementation
    ImageCropperPrivate* pimpl;
};

#endif // IMAGECROPPER_H
